const metrics = [
  ['Temperature', 'environment', 'temperature_c', '\u00b0C'],
  ['Humidity', 'environment', 'humidity_percent', '%'],
  ['Pressure', 'environment', 'pressure_hpa', 'hPa'],
  ['Light', 'environment', 'light_lux', 'lux'],
  ['UV Index', 'environment', 'uv_index', ''],
  ['PM1.0', 'particulate', 'pm1_ugm3', '\u00b5g/m\u00b3'],
  ['PM2.5', 'particulate', 'pm25_ugm3', '\u00b5g/m\u00b3'],
  ['PM10', 'particulate', 'pm10_ugm3', '\u00b5g/m\u00b3'],
  ['Wind Speed', 'wind', 'speed_mps', 'm/s']
];

const environmentReadings = document.querySelector('#environmentReadings');
const particulateReadings = document.querySelector('#particulateReadings');
const charts = document.querySelector('#charts');
let lastHistory = [];

metrics.forEach(([label, group, , unit], index) => {
  const target = group === 'environment' ? environmentReadings :
    (group === 'particulate' ? particulateReadings : null);
  if (target) {
    target.insertAdjacentHTML('beforeend', `
      <div class="reading-row">
        <span class="reading-label">${label}</span>
        <strong id="value${index}" class="reading-value">&mdash;</strong>
        <span class="reading-unit">${unit}</span>
      </div>`);
  }
  charts.insertAdjacentHTML('beforeend', `
    <section class="chart">
      <h3>${label} <small>${unit}</small></h3>
      <div class="chart-frame sunken-panel"><canvas id="chart${index}" aria-label="${label} trend chart"></canvas></div>
    </section>`);
});

function format(value) {
  return value == null ? '\u2014' : Number(value).toLocaleString(undefined, { maximumFractionDigits: 2 });
}

function path(row, group, key) {
  return row[group]?.[key] ?? null;
}

function formatUptime(milliseconds) {
  if (!Number.isFinite(milliseconds)) return '\u2014';
  const totalSeconds = Math.max(0, Math.floor(milliseconds / 1000));
  const days = Math.floor(totalSeconds / 86400);
  const hours = Math.floor((totalSeconds % 86400) / 3600);
  const minutes = Math.floor((totalSeconds % 3600) / 60);
  return days ? `${days}d ${hours}h ${minutes}m` : `${hours}h ${minutes}m`;
}

function formatCoordinate(value, positive, negative) {
  if (value == null || !Number.isFinite(Number(value))) return '\u2014';
  const numeric = Number(value);
  return `${Math.abs(numeric).toFixed(5)}\u00b0 ${numeric < 0 ? negative : positive}`;
}

function formatGnssUtc(value) {
  if (!value) return '\u2014';
  const date = new Date(value);
  if (Number.isNaN(date.getTime())) return '\u2014';
  const two = number => String(number).padStart(2, '0');
  return `${date.getUTCFullYear()}-${two(date.getUTCMonth() + 1)}-${two(date.getUTCDate())} ` +
    `${two(date.getUTCHours())}:${two(date.getUTCMinutes())}:${two(date.getUTCSeconds())}`;
}

function renderGnss(gnss = {}) {
  const fixLabels = {
    'FIX VALID': 'VALID',
    'FIX STALE': 'STALE',
    'COMMUNICATION OK - NO FIX': 'NO FIX',
    'NOT CONNECTED': 'NOT CONNECTED'
  };
  const fix = document.querySelector('#gnssFix');
  fix.textContent = fixLabels[gnss.state] ?? '\u2014';
  fix.classList.toggle('gnss-valid', gnss.fix_valid === true);
  document.querySelector('#gnssSatellites').textContent = gnss.satellites ?? '\u2014';
  document.querySelector('#gnssLatitude').textContent = formatCoordinate(gnss.latitude, 'N', 'S');
  document.querySelector('#gnssLongitude').textContent = formatCoordinate(gnss.longitude, 'E', 'W');
  document.querySelector('#gnssAltitude').textContent = gnss.altitude_m == null
    ? '\u2014' : `${format(gnss.altitude_m)} m`;
  document.querySelector('#gnssUtc').textContent = formatGnssUtc(gnss.utc);
}

function draw(canvas, rows, group, key) {
  const ratio = devicePixelRatio || 1;
  const width = Math.max(1, canvas.clientWidth);
  const height = Math.max(1, canvas.clientHeight);
  canvas.width = width * ratio;
  canvas.height = height * ratio;
  const context = canvas.getContext('2d');
  context.scale(ratio, ratio);
  context.clearRect(0, 0, width, height);
  context.fillStyle = '#ffffff';
  context.fillRect(0, 0, width, height);

  const points = rows.map((row, index) => [index, path(row, group, key)]).filter(([, value]) => value != null);
  context.strokeStyle = '#c0c0c0';
  context.lineWidth = 1;
  for (let y = 20; y < height; y += (height - 35) / 3) {
    context.beginPath();
    context.moveTo(0, y);
    context.lineTo(width, y);
    context.stroke();
  }
  if (points.length < 2) {
    context.fillStyle = '#404040';
    context.font = '11px "MS Sans Serif", Tahoma, sans-serif';
    context.fillText('Not enough data', 10, height / 2);
    return;
  }

  const values = points.map(([, value]) => value);
  const minimum = Math.min(...values);
  const maximum = Math.max(...values);
  const span = maximum - minimum || 1;
  context.strokeStyle = '#000080';
  context.lineWidth = 2;
  context.beginPath();
  points.forEach(([index, value], pointIndex) => {
    const x = (index / Math.max(1, rows.length - 1)) * width;
    const y = height - 15 - ((value - minimum) / span) * (height - 30);
    if (pointIndex) context.lineTo(x, y); else context.moveTo(x, y);
  });
  context.stroke();
  context.fillStyle = '#000000';
  context.font = '11px "MS Sans Serif", Tahoma, sans-serif';
  context.fillText(format(maximum), 5, 12);
  context.fillText(format(minimum), 5, height - 2);
}

function drawAllCharts() {
  metrics.forEach(([, group, key], index) => draw(document.querySelector(`#chart${index}`), lastHistory, group, key));
}

async function refresh() {
  const station = document.querySelector('#station').value.trim();
  const period = document.querySelector('#period');
  const hours = Number(period.value);
  const query = `station=${encodeURIComponent(station)}`;
  const start = new Date(Date.now() - hours * 3600000).toISOString();
  const error = document.querySelector('#error');
  error.hidden = true;
  error.textContent = '';
  document.querySelector('#statusReady').textContent = 'Loading...';
  document.querySelector('#periodLabel').textContent = period.options[period.selectedIndex].text;

  try {
    const [latestResponse, historyResponse] = await Promise.all([
      fetch(`/api/v1/measurements/latest?${query}`),
      fetch(`/api/v1/measurements?${query}&start=${encodeURIComponent(start)}&limit=15000`)
    ]);
    if (!latestResponse.ok) throw new Error(`Latest measurement: HTTP ${latestResponse.status}`);
    if (!historyResponse.ok) throw new Error(`History: HTTP ${historyResponse.status}`);

    const latest = await latestResponse.json();
    lastHistory = (await historyResponse.json()).reverse();
    metrics.forEach(([, group, key], index) => {
      const currentValue = document.querySelector(`#value${index}`);
      if (currentValue) currentValue.textContent = format(path(latest, group, key));
    });
    document.querySelector('#windSpeed').textContent = format(path(latest, 'wind', 'speed_mps'));
    document.querySelector('#windStatus').textContent = latest.wind?.status ?? 'NOT CONNECTED';
    renderGnss(latest.gnss);
    drawAllCharts();

    const received = new Date(latest.server_timestamp);
    const age = (Date.now() - received.getTime()) / 1000;
    const ageSeconds = Math.max(0, Math.round(age));
    const recent = age < 180;
    document.querySelector('#reportDot').classList.toggle('good', recent);
    document.querySelector('#reportStatus').textContent = recent ? 'ONLINE' : 'STALE';
    document.querySelector('#reportedAt').textContent = `Received: ${received.toLocaleString()}`;
    document.querySelector('#infoStation').textContent = latest.station_id;
    document.querySelector('#infoFirmware').textContent = latest.firmware_version;
    document.querySelector('#infoLast').textContent = `${ageSeconds} seconds ago`;
    document.querySelector('#infoUptime').textContent = formatUptime(latest.uptime_ms);
    document.querySelector('#sensorStatus').innerHTML = Object.entries(latest.health).map(([name, state]) => {
      const label = name.split('_').map(part => part.charAt(0).toUpperCase() + part.slice(1)).join(' ');
      const status = name === 'wind_speed' ? (latest.wind?.status ?? 'NOT CONNECTED') :
        (state.valid ? 'OK' : (state.stale ? 'STALE' : 'CHECK'));
      return `
      <div class="sensor ${status === 'OK' ? 'good' : ''}">
        <span>${label}</span>
        <span class="sensor-state">${status}</span>
      </div>`;
    }).join('');
    document.querySelector('#statusReady').textContent = 'Ready';
    document.querySelector('#statusConnection').textContent = `Station: ${recent ? 'Online' : 'Stale'} (${latest.station_id})`;
    document.querySelector('#statusTime').textContent = `Last update: ${received.toLocaleTimeString()}`;
  } catch (exception) {
    error.textContent = exception.message;
    error.hidden = false;
    document.querySelector('#statusReady').textContent = 'Error';
    document.querySelector('#statusConnection').textContent = 'Station: Unavailable';
  }
}

document.querySelector('#refresh').addEventListener('click', refresh);
document.querySelector('#period').addEventListener('change', refresh);
document.querySelector('#station').addEventListener('keydown', event => {
  if (event.key === 'Enter') refresh();
});

let resizeTimer;
window.addEventListener('resize', () => {
  clearTimeout(resizeTimer);
  resizeTimer = setTimeout(drawAllCharts, 100);
});

refresh();
setInterval(refresh, 30000);
