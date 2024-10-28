const int startPin = 2; // chân nút start
const int ledPin = 13;  // chân LED

volatile bool counting = false;
volatile unsigned long count = 0; // giá trị bộ đếm

void setup() {
  pinMode(startPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Thiết lập Timer1
  noInterrupts(); // Tắt tất cả các ngắt
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12); // Chế độ CTC, so sánh giá trị TCNT1 với OCR1A
  TCCR1B |= (1 << CS12);  // Prescaler 256
  OCR1A = 62499;          // Đặt số đếm để tạo tần số 1Hz
  TIMSK1 |= (1 << OCIE1A); // Kích hoạt ngắt khi Timer1 đạt giá trị so sánh
  interrupts();            // Bật lại ngắt

  attachInterrupt(digitalPinToInterrupt(startPin), startCounting, FALLING);
}

// ISR: Ngắt so sánh Timer1
ISR(TIMER1_COMPA_vect) {
  if (counting) {
    count++;
    int second = count % 60;
    int minute = (count / 60) % 60;
    int hour = (count / 3600) % 24;
    
    Serial.print("Bây giờ là: ");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);
  }
}

// Hàm xử lý khi nhấn nút start
void startCounting() {
  counting = !counting; // Đổi trạng thái giữa bắt đầu và dừng
  if (counting) {
    count = 0; // Đặt lại giá trị đếm khi bắt đầu
    digitalWrite(ledPin, HIGH); // Bật LED khi bắt đầu đếm
  } else {
    digitalWrite(ledPin, LOW);  // Tắt LED khi dừng đếm
  }
}

void loop() {
  // Không cần xử lý gì ở đây vì sử dụng ngắt
}
