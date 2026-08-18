param(
    [datetimeoffset]$Start = [datetimeoffset]::Parse('2026-08-20T09:00:00+08:00')
)

$ErrorActionPreference = 'Stop'
$culture = [Globalization.CultureInfo]::InvariantCulture
$rows = [System.Collections.Generic.List[object]]::new()
$temperatureDifferences = [System.Collections.Generic.List[double]]::new()
$humidityDifferences = [System.Collections.Generic.List[double]]::new()

function F2([double]$value) {
    return [string]::Format($culture, '{0:F2}', $value)
}

for ($i = 0; $i -lt 432; $i++) {
    $timestamp = $Start.AddMinutes(10 * $i)
    $hour = $timestamp.Hour + ($timestamp.Minute / 60.0)
    $dayPhase = 2.0 * [Math]::PI * ($hour - 6.0) / 24.0
    $daylight = if ($hour -ge 6 -and $hour -le 18) { [Math]::Max(0.0, [Math]::Sin([Math]::PI * ($hour - 6.0) / 12.0)) } else { 0.0 }

    $temperature = 28.5 + 3.5 * [Math]::Sin($dayPhase) + 0.15 * [Math]::Sin($i / 7.0)
    $referenceTemperature = $temperature - 0.18 + 0.04 * [Math]::Sin($i / 11.0)
    $humidity = 75.0 - 10.0 * [Math]::Sin($dayPhase) + 0.5 * [Math]::Sin($i / 9.0)
    $referenceHumidity = $humidity - 1.2 + 0.3 * [Math]::Sin($i / 13.0)
    $pressure = 1008.5 + 1.4 * [Math]::Sin($i / 120.0) + 0.25 * [Math]::Sin($i / 17.0)
    $uva = [Math]::Round(7200 * $daylight + 45 * [Math]::Abs([Math]::Sin($i / 5.0)))
    $windSpeed = 1.2 + 2.4 * [Math]::Abs([Math]::Sin($i / 18.0)) + 0.25 * [Math]::Sin($i / 3.0)
    $windDirection = (85 + 70 * [Math]::Sin($i / 26.0) + 360) % 360
    $solarInput = 6.5 * $daylight
    $battery = 3.92 + 0.18 * $daylight - 0.018 * [Math]::Floor($i / 144.0) - 0.025 * (($hour + 6.0) % 24.0) / 24.0

    $remoteReceived = if ($i -eq 184 -or $i -eq 185) { 0 } else { 1 }
    $backfilled = if ($remoteReceived -eq 0) { 1 } else { 0 }
    $gnssFix = if (($i % 97) -eq 0) { 0 } else { 1 }

    $temperatureDifferences.Add($temperature - $referenceTemperature)
    $humidityDifferences.Add($humidity - $referenceHumidity)

    $rows.Add([pscustomobject]@{
        timestamp_iso8601 = $timestamp.ToString('o')
        station_revision = 'HW-v0.2-preview'
        firmware_revision = 'FW-v0.2-preview'
        evidence_level = 'synthetic_preview'
        temperature_c = F2 $temperature
        reference_temperature_c = F2 $referenceTemperature
        relative_humidity_percent = F2 $humidity
        reference_relative_humidity_percent = F2 $referenceHumidity
        pressure_hpa = F2 $pressure
        uva_counts = [int]$uva
        wind_speed_mps = F2 ([Math]::Max(0.0, $windSpeed))
        wind_direction_deg = F2 $windDirection
        battery_v = F2 $battery
        solar_input_w = F2 $solarInput
        gnss_fix = $gnssFix
        local_logged = 1
        remote_received = $remoteReceived
        backfilled = $backfilled
        restart_count = 0
        sensor_status = 'ok'
    })
}

$dataPath = Join-Path $PSScriptRoot 'synthetic-72h-data.csv'
$rows | Export-Csv -LiteralPath $dataPath -NoTypeInformation -Encoding utf8

$batteryValues = $rows | ForEach-Object { [double]::Parse($_.battery_v, $culture) }
$summary = [ordered]@{
    evidence_level = 'synthetic_preview'
    expected_records = 432
    local_records = @($rows | Where-Object local_logged -eq 1).Count
    remote_records_during_interval = @($rows | Where-Object remote_received -eq 1).Count
    backfilled_records = @($rows | Where-Object backfilled -eq 1).Count
    restarts = ($rows | Measure-Object restart_count -Maximum).Maximum
    minimum_battery_v = [Math]::Round(($batteryValues | Measure-Object -Minimum).Minimum, 2)
    maximum_battery_v = [Math]::Round(($batteryValues | Measure-Object -Maximum).Maximum, 2)
    mean_temperature_difference_c = [Math]::Round(($temperatureDifferences | Measure-Object -Average).Average, 3)
    maximum_absolute_temperature_difference_c = [Math]::Round(($temperatureDifferences | ForEach-Object { [Math]::Abs($_) } | Measure-Object -Maximum).Maximum, 3)
    mean_humidity_difference_percent = [Math]::Round(($humidityDifferences | Measure-Object -Average).Average, 3)
    maximum_absolute_humidity_difference_percent = [Math]::Round(($humidityDifferences | ForEach-Object { [Math]::Abs($_) } | Measure-Object -Maximum).Maximum, 3)
    decision = 'PROCEED_TO_NEXT_SUPERVISED_TEST_IN_SIMULATION'
}

$summary | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $PSScriptRoot 'summary.json') -Encoding utf8
$summary | ConvertTo-Json

