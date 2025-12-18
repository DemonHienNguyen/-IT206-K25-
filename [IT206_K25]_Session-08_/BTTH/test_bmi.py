"""Các test case đơn giản cho lớp BMI_Calculator.

File này sử dụng unittest để kiểm thử:
    - Tính đúng BMI cho một số trường hợp cơ bản.
    - Phân loại cơ thể đúng với các ngưỡng BMI.
    - Chạy thử với danh sách 10 người dùng khác nhau.
"""

import unittest

from bmi_calculator import BMI_Calculator


class TestBMICalculatorBasic(unittest.TestCase):
    """Các test cơ bản cho phân loại BMI."""

    def test_underweight_category(self):
        """Test case 1: Người có BMI < 18.5 -> Gầy."""
        # height = 1.7, weight = 50 -> BMI ~ 17.30
        person = BMI_Calculator(name="User1", height=1.7, weight=50)
        bmi = person.calculate_bmi()
        self.assertLess(bmi, 18.5)
        self.assertEqual(person.get_category(), "Gầy")

    def test_normal_category(self):
        """Test case 2: Người có BMI từ 18.5–24.9 -> Bình thường."""
        # height = 1.7, weight = 65 -> BMI ~ 22.49
        person = BMI_Calculator(name="User2", height=1.7, weight=65)
        bmi = person.calculate_bmi()
        self.assertGreaterEqual(bmi, 18.5)
        self.assertLess(bmi, 25)
        self.assertEqual(person.get_category(), "Bình thường")

    def test_obese_category(self):
        """Test case 3: Người có BMI >= 30 -> Béo phì."""
        # height = 1.6, weight = 80 -> BMI ~ 31.25
        person = BMI_Calculator(name="User3", height=1.6, weight=80)
        bmi = person.calculate_bmi()
        self.assertGreaterEqual(bmi, 30)
        self.assertEqual(person.get_category(), "Béo phì")


class TestBMICalculatorBulk(unittest.TestCase):
    """Test với danh sách nhiều người dùng để minh họa cho sinh viên."""

    def test_bulk_users(self):
        """Tạo 10 người dùng và kiểm thử nhanh BMI + category.

        Ở đây chúng ta không kiểm tra chính xác mọi giá trị BMI,
        mà chủ yếu minh họa cách duyệt danh sách và gọi các phương thức.
        """
        users_data = [
            # name, height (m), weight (kg)
            ("An", 1.70, 50),   # Gầy
            ("Bình", 1.65, 60),  # Bình thường
            ("Chi", 1.60, 48),   # Gầy
            ("Dung", 1.75, 80),  # Thừa cân
            ("Em", 1.55, 70),    # Béo phì (gần ngưỡng)
            ("Phúc", 1.80, 90),  # Thừa cân/Béo phì tùy BMI
            ("Giang", 1.68, 72),  # Thừa cân
            ("Hà", 1.50, 40),    # Gầy
            ("Khanh", 1.72, 68),  # Bình thường
            ("Lan", 1.60, 90),   # Béo phì
        ]

        users: list[BMI_Calculator] = []

        # Tạo đối tượng từ dữ liệu và đảm bảo không có lỗi
        for name, height, weight in users_data:
            person = BMI_Calculator(name=name, height=height, weight=weight)
            users.append(person)

        # Kiểm tra số lượng đối tượng tạo ra
        self.assertEqual(len(users), 10)

        # Kiểm tra nhanh: tất cả BMI đều > 0 và category là một trong 4 loại
        valid_categories = {"Gầy", "Bình thường", "Thừa cân", "Béo phì"}

        for person in users:
            bmi = person.calculate_bmi()
            category = person.get_category()

            # BMI luôn dương vì height, weight đều > 0
            self.assertGreater(bmi, 0)
            # Phân loại phải thuộc một trong các loại đã định nghĩa
            self.assertIn(category, valid_categories)

            # Gọi thêm display_info() để đảm bảo không lỗi định dạng chuỗi
            info_str = person.display_info()
            self.assertIsInstance(info_str, str)
            self.assertGreater(len(info_str), 0)


if __name__ == "__main__":
    # Cho phép chạy file trực tiếp để xem kết quả test
    unittest.main()