// Callback otomatis saat menerima pesan dari node manapun di jaringan mesh dengan filter suhu kritis
void receivedCallback(uint32_t from, String &msg) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, msg);

  if (!error) {
    const char* sender = doc["node"];
    uint32_t chipId   = doc["chipId"];
    float suhu        = doc["suhu"];
    float kelembapan  = doc["kelembapan"];

    // Kondisi filter ambang batas suhu kritis (> 32.0 °C)
    if (suhu > 32.0) {
      Serial.println("========================================");
      Serial.printf("[PERINGATAN] SUHU KRITIS TERDETEKSI!\n");
      Serial.printf("[PENGIRIM] %s (Node ID: %u | Chip ID: %u)\n", sender, from, chipId);
      Serial.printf("Suhu       : %.2f °C (Melahahi Ambang Batas!)\n", suhu);
      Serial.printf("Kelembapan : %.2f %%\n", kelembapan);
      Serial.println("========================================");
    } else {
      // Status singkat jika suhu dalam kondisi normal (<= 32.0 °C)
      Serial.printf("[NORMAL] Telemetri dari Node %u aman (Suhu: %.2f °C)\n", chipId, suhu);
    }
  } else {
    Serial.printf("[TERIMA DATA MENTAH DARI %u]: %s\n", from, msg.c_str());
  }
}