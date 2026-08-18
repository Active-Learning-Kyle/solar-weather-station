$ErrorActionPreference = 'Stop'
$repo = Split-Path $PSScriptRoot -Parent

function Assert-True([bool]$condition, [string]$message) {
    if (-not $condition) { throw "FAILED: $message" }
    Write-Output "PASS: $message"
}

& (Join-Path $PSScriptRoot 'synthetic-v0.2/generate-preview.ps1') | Out-Null

$data = Import-Csv -LiteralPath (Join-Path $PSScriptRoot 'synthetic-v0.2/synthetic-72h-data.csv')
Assert-True ($data.Count -eq 432) '72-hour preview has 432 ten-minute records'
Assert-True (@($data | Where-Object evidence_level -ne 'synthetic_preview').Count -eq 0) 'every generated row is labelled synthetic_preview'
Assert-True (@($data | Where-Object local_logged -eq '1').Count -eq 432) 'local preview contains all records'
Assert-True (@($data | Where-Object remote_received -eq '1').Count -eq 430) 'remote preview contains the intended two-interval live gap'
Assert-True (@($data | Where-Object backfilled -eq '1').Count -eq 2) 'both remote gaps are visibly backfilled'

$summary = Get-Content -LiteralPath (Join-Path $PSScriptRoot 'synthetic-v0.2/summary.json') -Raw | ConvertFrom-Json
Assert-True ($summary.minimum_battery_v -gt 3.70) 'synthetic battery floor exceeds the preview threshold'
Assert-True ($summary.restarts -eq 0) 'synthetic case contains zero restarts'

$bom = Import-Csv -LiteralPath (Join-Path $repo 'bom/bom.csv')
$total = $bom | Where-Object item_id -eq 'SYS-001'
Assert-True ($total.unit_cost -eq '3715' -and $total.currency -eq 'HKD') 'BOM exposes the HKD 3715 preview total'

$matrix = Import-Csv -LiteralPath (Join-Path $PSScriptRoot 'test-matrix.csv')
Assert-True ($matrix.Count -ge 31) 'test matrix includes the v0.2 preview and real replacement tests'

$missing = [System.Collections.Generic.List[string]]::new()
Get-ChildItem -LiteralPath $repo -Recurse -Filter '*.md' | ForEach-Object {
    $file = $_
    $text = Get-Content -LiteralPath $file.FullName -Raw
    [regex]::Matches($text, '\[[^\]]+\]\(([^)]+)\)') | ForEach-Object {
        $target = $_.Groups[1].Value
        if ($target -notmatch '^(https?://|mailto:|#|<)') {
            $plain = ($target -split '#')[0]
            if ($plain) {
                $resolved = [IO.Path]::GetFullPath((Join-Path $file.DirectoryName $plain))
                if (-not (Test-Path -LiteralPath $resolved)) { $missing.Add("$($file.FullName) -> $target") }
            }
        }
    }
}
Assert-True ($missing.Count -eq 0) 'all local Markdown links resolve'

Write-Output 'TEACHING PREVIEW VALIDATION COMPLETE'

