import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QLabel, QPushButton, QMessageBox
from PySide6.QtCore import Qt, __version__ as QT_VERSION

class Qt6PythonDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Qt6 PySide6 Verification Demo")
        self.resize(500, 350)
        self.click_count = 0

        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)

        layout = QVBoxLayout(central_widget)
        layout.setContentsMargins(30, 30, 30, 30)
        layout.setSpacing(20)

        title = QLabel("✨ PySide6 / Qt 6 Installed Successfully!", self)
        title.setStyleSheet("font-size: 20px; font-weight: bold; color: #00E676;")
        title.setAlignment(Qt.AlignmentFlag.AlignCenter)

        info = QLabel(f"<b>PySide6 (Qt) Version:</b> {QT_VERSION}<br><b>Python Version:</b> {sys.version.split()[0]}", self)
        info.setStyleSheet("background-color: #1E293B; color: #E2E8F0; border-radius: 10px; padding: 15px; font-size: 14px;")

        self.counter_label = QLabel("Button Clicks: 0", self)
        self.counter_label.setStyleSheet("font-size: 16px; font-weight: 600; color: #94A3B8;")
        self.counter_label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        btn = QPushButton("🚀 Click Me to Test Python Qt Event Loop", self)
        btn.setStyleSheet("background-color: #3B82F6; color: white; font-weight: bold; font-size: 14px; padding: 12px; border-radius: 8px;")
        btn.clicked.connect(self.on_click)

        layout.addWidget(title)
        layout.addWidget(info)
        layout.addWidget(self.counter_label)
        layout.addWidget(btn)

        self.setStyleSheet("QMainWindow { background-color: #0F172A; }")

    def on_click(self):
        self.click_count += 1
        self.counter_label.setText(f"Button Clicks: {self.click_count}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Qt6PythonDemo()
    window.show()
    sys.exit(app.exec())
