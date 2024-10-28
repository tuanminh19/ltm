// Định nghĩa các chân
const int PUL_PIN = 12;  // Chân Pul
const int DIR_PIN = 13;  // Chân Dir

bool direction = true;  // true = xuôi, false = ngược

void setup() {
  pinMode(PUL_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  Serial.begin(9600);  // Khởi động Serial
  Serial.println("setup done");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // Đọc lệnh từ Serial

    if (command == 'f') {  // Nhấn phím 'f' để quay xuôi
      direction = true;
    } else if (command == 'b') {  // Nhấn phím 'b' để quay ngược
      direction = false;
    }
  }

  // Đặt chiều quay
  digitalWrite(DIR_PIN, direction ? HIGH : LOW);
  
  // Quay motor liên tục
  rotateMotor();
}

void rotateMotor() {
  digitalWrite(PUL_PIN, HIGH);
  delayMicroseconds(1000);  // Thời gian xung cao
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(1000);  // Thời gian xung thấp
}

