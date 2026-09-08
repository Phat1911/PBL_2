#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSysInfo>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGlobal>

class Qt6DemoWindow : public QMainWindow {
public:
  Qt6DemoWindow(QWidget *parent = nullptr)
      : QMainWindow(parent), m_clickCount(0) {
    setWindowTitle("Qt6 Installation Verification Demo");
    resize(500, 380);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    // Header Title
    QLabel *titleLabel = new QLabel("✨ Qt 6 Installed Successfully!", this);
    titleLabel->setStyleSheet(
        "font-size: 22px; font-weight: bold; color: #00E676; "
        "margin-bottom: 5px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Information Card
    QLabel *infoLabel = new QLabel(this);
    QString infoText = QString("<b>Qt Version:</b> %1<br>"
                               "<b>Compiler:</b> MinGW 13.1.0 (64-bit)<br>"
                               "<b>OS Architecture:</b> %2<br>"
                               "<b>Build Engine:</b> CMake + Ninja")
                           .arg(qVersion(), QSysInfo::currentCpuArchitecture());

    infoLabel->setText(infoText);
    infoLabel->setStyleSheet(
        "background-color: #1E293B; color: #E2E8F0; border-radius: 10px; "
        "padding: 16px; font-size: 14px; line-height: 1.6;");

    // Counter Section
    m_counterLabel = new QLabel("Button Clicks: 0", this);
    m_counterLabel->setStyleSheet(
        "font-size: 16px; font-weight: 600; color: #94A3B8;");
    m_counterLabel->setAlignment(Qt::AlignCenter);

    QPushButton *clickBtn =
        new QPushButton("🚀 Click Me to Test Qt Event Loop", this);
    clickBtn->setCursor(Qt::PointingHandCursor);
    clickBtn->setStyleSheet(
        "QPushButton {"
        "   background: linear-gradient(135deg, #3B82F6, #2563EB);"
        "   color: white; font-weight: bold; font-size: 14px;"
        "   border-radius: 8px; padding: 12px 20px; border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: #60A5FA;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1D4ED8;"
        "}");

    connect(clickBtn, &QPushButton::clicked, this, [this]() {
      m_clickCount++;
      m_counterLabel->setText(QString("Button Clicks: %1").arg(m_clickCount));
    });

    // About Qt Button
    QPushButton *aboutQtBtn = new QPushButton("ℹ️ About Qt Framework", this);
    aboutQtBtn->setCursor(Qt::PointingHandCursor);
    aboutQtBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #334155; color: #F8FAFC; font-size: 13px;"
        "   border-radius: 8px; padding: 10px 16px; border: 1px solid #475569;"
        "}"
        "QPushButton:hover {"
        "   background-color: #475569;"
        "}");

    connect(aboutQtBtn, &QPushButton::clicked, this,
            [this]() { QMessageBox::aboutQt(this, "About Installed Qt6"); });

    // Layout Assembly
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(infoLabel);
    mainLayout->addWidget(m_counterLabel);
    mainLayout->addWidget(clickBtn);
    mainLayout->addWidget(aboutQtBtn);

    // Main Window Styling
    setStyleSheet("QMainWindow { background-color: #0F172A; }");
  }

private:
  int m_clickCount;
  QLabel *m_counterLabel;
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Qt6DemoWindow window;
  window.show();
  return app.exec();
}
