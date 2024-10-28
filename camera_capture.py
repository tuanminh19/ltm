import cv2
import os

# Địa chỉ IP của camera 
#url = 'http://192.168.100.31:4747/video'  # Địa chỉ IP từ ứng dụng IP Webcam

# Mở kết nối video
cap = cv2.VideoCapture(url)

# Kiểm tra xem camera có mở thành công không
if not cap.isOpened():
    print("Không thể kết nối với camera !")
    exit()

# Tìm số thứ tự của file tiếp theo (photo1.jpg, photo2.jpg,...)
photo_count = 1
while os.path.exists(f'photo{photo_count}.jpg'):
    photo_count += 1

while True:
    # Đọc khung hình từ camera
    ret, frame = cap.read()

    # Kiểm tra xem có đọc được khung hình không
    if not ret:
        print("Không thể đọc khung hình từ camera !")
        break

    # Hiển thị khung hình
    cv2.imshow('Camera từ điện thoại', frame)

    # Đọc phím bấm
    key = cv2.waitKey(1) & 0xFF

    # Nếu nhấn phím 's', chụp ảnh và lưu vào tệp
    if key == ord('s'):
        # Tạo tên tệp động với biến photo_count
        filename = f'photo{photo_count}.jpg'
        cv2.imwrite(filename, frame)
        print(f"Ảnh đã được lưu với tên '{filename}'")
        
        # Tăng biến đếm để chuẩn bị cho ảnh tiếp theo
        photo_count += 1

    # Nếu nhấn phím 'q', thoát khỏi vòng lặp
    elif key == ord('q'):
        print("Thoát khỏi chương trình")
        break

# Giải phóng tài nguyên camera và đóng cửa sổ hiển thị
cap.release()
cv2.destroyAllWindows()
