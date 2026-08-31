#include "HttpDataUploader.h"

#include "WeatherDataSerializer.h"
#include "app_config.h"
#include "core/NetworkManager.h"

#include <HTTPClient.h>
#include <WiFiClient.h>

#if __has_include("secrets.h")
#include "secrets.h"
#else
#define BACKEND_HOST ""
#define BACKEND_PORT 8000
#define BACKEND_ENDPOINT "/api/v1/measurements"
#endif

namespace
{
QueueHandle_t uploadQueue = nullptr;
portMUX_TYPE statusMutex = portMUX_INITIALIZER_UNLOCKED;
UploadStatus uploadStatus = {};
}

void HttpDataUploader::begin()
{
    if (BACKEND_HOST[0] == '\0')
    {
        Serial.println("HTTP uploader disabled: backend is not configured");
        return;
    }

    uploadQueue = xQueueCreate(1, sizeof(WeatherData));
    if (uploadQueue == nullptr)
    {
        Serial.println("HTTP uploader failed to create its queue");
        return;
    }
    xTaskCreate(task, "http-uploader", 8192, nullptr, 1, nullptr);
}

bool HttpDataUploader::enqueue(const WeatherData& data)
{
    if (uploadQueue == nullptr)
        return false;
    return xQueueOverwrite(uploadQueue, &data) == pdPASS;
}

UploadStatus HttpDataUploader::status()
{
    portENTER_CRITICAL(&statusMutex);
    UploadStatus snapshot = uploadStatus;
    portEXIT_CRITICAL(&statusMutex);
    return snapshot;
}

void HttpDataUploader::recordResult(bool success, int responseCode)
{
    portENTER_CRITICAL(&statusMutex);
    uploadStatus.lastHttpResponseCode = responseCode;
    if (success)
    {
        ++uploadStatus.successfulUploads;
        uploadStatus.consecutiveFailures = 0;
        uploadStatus.lastSuccessfulUploadMs = millis();
    }
    else
    {
        ++uploadStatus.failedUploads;
        ++uploadStatus.consecutiveFailures;
    }
    portEXIT_CRITICAL(&statusMutex);
}

void HttpDataUploader::task(void*)
{
    WeatherData data;
    for (;;)
    {
        if (xQueueReceive(uploadQueue, &data, portMAX_DELAY) != pdTRUE)
            continue;

        if (!Core::NetworkManager::isWiFiConnected())
        {
            recordResult(false, 0);
            continue;
        }

        const String payload = WeatherDataSerializer::toJson(data, millis());
        const String url = String("http://") + BACKEND_HOST + ":" +
                           String(BACKEND_PORT) + BACKEND_ENDPOINT;
        WiFiClient client;
        HTTPClient http;
        http.setConnectTimeout(AppConfig::HttpConnectTimeoutMs);
        http.setTimeout(AppConfig::HttpReadTimeoutMs);

        int responseCode = -1;
        if (http.begin(client, url))
        {
            http.addHeader("Content-Type", "application/json");
            responseCode = http.POST(payload);
            http.end();
        }
        const bool success = responseCode >= 200 && responseCode < 300;
        recordResult(success, responseCode);
        Serial.print("HTTP upload: ");
        Serial.print(success ? "OK" : "FAILED");
        Serial.print(" (code=");
        Serial.print(responseCode);
        Serial.println(")");
    }
}
