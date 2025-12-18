"""BMI Calculator module.

This module defines the `BMI_Calculator` class dùng để tính chỉ số BMI,
phân loại cơ thể và hiển thị thông tin người dùng. Đồng thời module cũng
cung cấp một giao diện dòng lệnh (CLI) đơn giản để sinh viên thực hành.
"""


class BMI_Calculator:
    """Lớp tính chỉ số BMI cho một người dùng.

    Thuộc tính:
        name (str): Tên người dùng.
        height (float): Chiều cao (m).
        weight (float): Cân nặng (kg).

    Ví dụ:
        >>> person = BMI_Calculator("An", 1.7, 60)
        >>> bmi = person.calculate_bmi()
        >>> category = person.get_category()
    """

    def __init__(self, name: str, height: float, weight: float) -> None:
        """Khởi tạo đối tượng BMI_Calculator.

        Args:
            name (str): Tên người dùng.
            height (float): Chiều cao (m), phải > 0.
            weight (float): Cân nặng (kg), phải > 0.

        Raises:
            ValueError: Nếu height <= 0 hoặc weight <= 0.
        """
        if height <= 0:
            # Kiểm tra dữ liệu đầu vào để tránh chia cho 0
            raise ValueError("Chiều cao phải lớn hơn 0.")
        if weight <= 0:
            raise ValueError("Cân nặng phải lớn hơn 0.")

        self.name = name
        self.height = float(height)
        self.weight = float(weight)

    def calculate_bmi(self) -> float:
        """Tính chỉ số BMI theo công thức chuẩn.

        Công thức:
            BMI = weight / (height ** 2)

        Returns:
            float: Giá trị BMI (không làm tròn).
        """
        bmi = self.weight / (self.height ** 2)
        return bmi

    def get_category(self) -> str:
        """Trả về phân loại cơ thể dựa trên chỉ số BMI.

        Quy tắc phân loại:
            - BMI < 18.5       -> "Gầy"
            - 18.5 <= BMI < 25 -> "Bình thường"
            - 25 <= BMI < 30   -> "Thừa cân"
            - BMI >= 30        -> "Béo phì"

        Returns:
            str: Chuỗi mô tả phân loại cơ thể.
        """
        bmi = self.calculate_bmi()

        # Dựa trên khoảng BMI để phân loại
        if bmi < 18.5:
            return "Gầy"
        if 18.5 <= bmi < 25:
            return "Bình thường"
        if 25 <= bmi < 30:
            return "Thừa cân"
        return "Béo phì"

    def display_info(self) -> str:
        """Tạo chuỗi thông tin đầy đủ của người dùng.

        Chuỗi bao gồm:
            - Tên
            - Chiều cao
            - Cân nặng
            - Chỉ số BMI (làm tròn 2 chữ số)
            - Phân loại cơ thể

        Returns:
            str: Chuỗi thông tin đã định dạng.
        """
        bmi_value = self.calculate_bmi()
        category = self.get_category()

        # Làm tròn BMI cho dễ nhìn khi hiển thị
        bmi_rounded = round(bmi_value, 2)

        info = (
            f"Tên: {self.name}, "
            f"Chiều cao: {self.height:.2f} m, "
            f"Cân nặng: {self.weight:.2f} kg, "
            f"BMI: {bmi_rounded:.2f}, "
            f"Phân loại: {category}"
        )
        return info


# ==========================
# Phần CLI (Command Line Interface)
# ==========================


def _print_menu() -> None:
    """In menu lựa chọn cho người dùng."""
    print("\n=== BMI Calculator ===")
    print("1. Nhập thông tin người dùng")
    print("2. Tính và hiển thị kết quả BMI")
    print("3. Thoát chương trình")


def _input_user() -> BMI_Calculator:
    """Nhập thông tin một người dùng từ bàn phím.

    Hỏi lần lượt: tên, chiều cao (m), cân nặng (kg).

    Returns:
        BMI_Calculator: Đối tượng được tạo từ thông tin đã nhập.

    Raises:
        ValueError: Nếu người dùng nhập giá trị không hợp lệ.
    """
    name = input("Nhập tên: ").strip()
    height_str = input("Nhập chiều cao (m): ").strip()
    weight_str = input("Nhập cân nặng (kg): ").strip()

    # Chuyển đổi chuỗi sang float; có thể phát sinh ValueError nếu không hợp lệ
    height = float(height_str)
    weight = float(weight_str)

    return BMI_Calculator(name=name, height=height, weight=weight)


def _print_table(users: list[BMI_Calculator]) -> None:
    """In bảng kết quả BMI cho danh sách người dùng.

    Bảng gồm các cột:
        - Tên
        - Chiều cao
        - Cân nặng
        - BMI
        - Phân loại

    Args:
        users (list[BMI_Calculator]): Danh sách đối tượng người dùng.
    """
    if not users:
        print("Chưa có dữ liệu người dùng. Vui lòng chọn 1 để nhập thông tin.")
        return

    # Độ rộng cột cơ bản để bảng dễ nhìn
    name_width = 15
    height_width = 12
    weight_width = 12
    bmi_width = 8
    category_width = 12

    # In tiêu đề bảng
    header = (
        f"{'Tên':<{name_width}}"
        f"{'Chiều cao':<{height_width}}"
        f"{'Cân nặng':<{weight_width}}"
        f"{'BMI':<{bmi_width}}"
        f"{'Phân loại':<{category_width}}"
    )
    print("\nKết quả BMI:")
    print("-" * len(header))
    print(header)
    print("-" * len(header))

    # In từng dòng dữ liệu
    for user in users:
        bmi_value = user.calculate_bmi()
        bmi_rounded = round(bmi_value, 2)
        category = user.get_category()
        row = (
            f"{user.name:<{name_width}}"
            f"{user.height:<{height_width}.2f}"
            f"{user.weight:<{weight_width}.2f}"
            f"{bmi_rounded:<{bmi_width}.2f}"
            f"{category:<{category_width}}"
        )
        print(row)

    print("-" * len(header))


def main() -> None:
    """Hàm main chạy ứng dụng CLI BMI Calculator.

    Vòng lặp chính:
        1. Hiển thị menu.
        2. Nhận lựa chọn từ người dùng.
        3. Thực hiện chức năng tương ứng.
    """
    users: list[BMI_Calculator] = []

    while True:
        _print_menu()
        choice = input("Chọn chức năng (1-3): ").strip()

        if choice == "1":
            # Nhập thông tin và lưu lại vào danh sách
            try:
                user = _input_user()
                users.append(user)
                print("Đã thêm người dùng thành công.")
            except ValueError as exc:
                print(f"Lỗi dữ liệu: {exc}. Vui lòng thử lại.")
        elif choice == "2":
            # In bảng kết quả BMI cho toàn bộ người dùng đã nhập
            _print_table(users)
        elif choice == "3":
            print("Thoát chương trình. Tạm biệt!")
            break
        else:
            print("Lựa chọn không hợp lệ. Vui lòng chọn 1, 2 hoặc 3.")


if __name__ == "__main__":
    main()


# ---------------------------------------------------------
# Giải thích logic hoạt động tổng quát của chương trình:
#
# - Lớp BMI_Calculator lưu thông tin một người (tên, chiều cao, cân nặng)
#   và cung cấp các phương thức:
#       + calculate_bmi(): tính BMI = cân nặng / (chiều cao^2)
#       + get_category(): dựa trên BMI để phân loại Gầy/Bình thường/Thừa cân/Béo phì
#       + display_info(): trả về chuỗi thông tin đầy đủ, dễ đọc.
#
# - Luồng xử lý trong CLI:
#       1. Người dùng chạy chương trình -> hàm main() được gọi.
#       2. Chương trình hiển thị menu (1: nhập thông tin, 2: xem kết quả, 3: thoát).
#       3. Khi người dùng chọn 1:
#           - Chương trình yêu cầu nhập tên, chiều cao, cân nặng.
#           - Tạo đối tượng BMI_Calculator và lưu vào danh sách users.
#       4. Khi người dùng chọn 2:
#           - Chương trình duyệt qua danh sách users.
#           - Tính BMI, phân loại, rồi in kết quả dưới dạng bảng gọn gàng.
#       5. Khi người dùng chọn 3:
#           - Thoát vòng lặp và kết thúc chương trình.
#
# - Nhờ tách riêng lớp BMI_Calculator và phần CLI, các file test có thể
#   import BMI_Calculator bình thường mà không bị ảnh hưởng bởi chương trình chính.
# ---------------------------------------------------------