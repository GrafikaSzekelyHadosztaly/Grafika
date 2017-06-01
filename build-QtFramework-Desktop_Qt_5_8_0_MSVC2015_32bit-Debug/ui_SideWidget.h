/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QComboBox *_select_img;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *_select_index;
    QTabWidget *tabWidget;
    QWidget *tab;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QGroupBox *groupBox_3;
    QWidget *tab_2;
    QGroupBox *groupBox_4;
    QSpinBox *file_index_spin;
    QPushButton *read_btn;
    QGroupBox *groupBox_5;
    QSpinBox *patch_index_spin;
    QComboBox *select_shader;
    QComboBox *select_material;
    QLabel *label_10;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_12;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_2;
    QDoubleSpinBox *doubleSpinBox_3;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QStringLiteral("SideWidget"));
        SideWidget->resize(289, 699);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 211));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 261, 201));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QStringLiteral("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QStringLiteral("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QStringLiteral("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QStringLiteral("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.0001);
        zoom_factor_spin_box->setMaximum(10000);
        zoom_factor_spin_box->setSingleStep(0.1);
        zoom_factor_spin_box->setValue(1);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QStringLiteral("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100);
        trans_x_spin_box->setMaximum(100);
        trans_x_spin_box->setSingleStep(0.1);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QStringLiteral("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100);
        trans_y_spin_box->setMaximum(100);
        trans_y_spin_box->setSingleStep(0.1);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QStringLiteral("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100);
        trans_z_spin_box->setMaximum(100);
        trans_z_spin_box->setSingleStep(0.1);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        _select_img = new QComboBox(SideWidget);
        _select_img->setObjectName(QStringLiteral("_select_img"));
        _select_img->setGeometry(QRect(10, 240, 151, 22));
        label_8 = new QLabel(SideWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 220, 71, 16));
        label_9 = new QLabel(SideWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(180, 220, 101, 16));
        _select_index = new QComboBox(SideWidget);
        _select_index->setObjectName(QStringLiteral("_select_index"));
        _select_index->setGeometry(QRect(180, 240, 69, 22));
        tabWidget = new QTabWidget(SideWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 470, 271, 221));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(60, 10, 42, 22));
        spinBox_2 = new QSpinBox(tab);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(60, 110, 42, 22));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(120, 10, 120, 80));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(10, 20, 16, 17));
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 40, 16, 17));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 60, 16, 17));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(40, 60, 16, 17));
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(70, 60, 16, 17));
        radioButton_6 = new QRadioButton(groupBox_2);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(70, 40, 16, 17));
        radioButton_7 = new QRadioButton(groupBox_2);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(70, 20, 16, 17));
        radioButton_8 = new QRadioButton(groupBox_2);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(40, 20, 16, 17));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(120, 110, 120, 80));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        groupBox_4 = new QGroupBox(SideWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 270, 141, 51));
        file_index_spin = new QSpinBox(groupBox_4);
        file_index_spin->setObjectName(QStringLiteral("file_index_spin"));
        file_index_spin->setGeometry(QRect(10, 20, 42, 22));
        read_btn = new QPushButton(groupBox_4);
        read_btn->setObjectName(QStringLiteral("read_btn"));
        read_btn->setGeometry(QRect(60, 20, 75, 23));
        groupBox_5 = new QGroupBox(SideWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 320, 271, 101));
        patch_index_spin = new QSpinBox(groupBox_5);
        patch_index_spin->setObjectName(QStringLiteral("patch_index_spin"));
        patch_index_spin->setGeometry(QRect(10, 20, 42, 22));
        select_shader = new QComboBox(groupBox_5);
        select_shader->setObjectName(QStringLiteral("select_shader"));
        select_shader->setGeometry(QRect(60, 20, 111, 22));
        select_material = new QComboBox(groupBox_5);
        select_material->setObjectName(QStringLiteral("select_material"));
        select_material->setGeometry(QRect(180, 20, 81, 22));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 50, 47, 13));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 70, 16, 16));
        doubleSpinBox = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(20, 70, 62, 22));
        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(100, 70, 16, 20));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(190, 70, 16, 16));
        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(110, 70, 62, 22));
        doubleSpinBox_3 = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setGeometry(QRect(200, 70, 62, 22));
#ifndef QT_NO_SHORTCUT
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
#endif // QT_NO_SHORTCUT

        retranslateUi(SideWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QApplication::translate("SideWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SideWidget", "Transformations", Q_NULLPTR));
        label->setText(QApplication::translate("SideWidget", "Rotate around x", Q_NULLPTR));
        label_2->setText(QApplication::translate("SideWidget", "Rotate around y", Q_NULLPTR));
        label_3->setText(QApplication::translate("SideWidget", "Rotate around z", Q_NULLPTR));
        label_4->setText(QApplication::translate("SideWidget", "Zoom factor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("SideWidget", "Translate along x", Q_NULLPTR));
        label_6->setText(QApplication::translate("SideWidget", "Translate along y", Q_NULLPTR));
        label_7->setText(QApplication::translate("SideWidget", "Translate along z", Q_NULLPTR));
        _select_img->clear();
        _select_img->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "Parametric curves", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Cyclic curve", Q_NULLPTR)
         << QApplication::translate("SideWidget", "OFF file", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Parametric surfaces", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Bezier", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Shader", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Fancy triangle", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Hermite patch teszt", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Composite Hermite Surface", Q_NULLPTR)
        );
        label_8->setText(QApplication::translate("SideWidget", "Select image", Q_NULLPTR));
        label_9->setText(QApplication::translate("SideWidget", "Select image index", Q_NULLPTR));
        _select_index->clear();
        _select_index->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "1", Q_NULLPTR)
         << QApplication::translate("SideWidget", "2", Q_NULLPTR)
         << QApplication::translate("SideWidget", "3", Q_NULLPTR)
         << QApplication::translate("SideWidget", "4", Q_NULLPTR)
         << QApplication::translate("SideWidget", "5", Q_NULLPTR)
        );
        groupBox_2->setTitle(QApplication::translate("SideWidget", "GroupBox", Q_NULLPTR));
        radioButton->setText(QString());
        radioButton_2->setText(QString());
        radioButton_3->setText(QString());
        radioButton_4->setText(QString());
        radioButton_5->setText(QString());
        radioButton_6->setText(QString());
        radioButton_7->setText(QString());
        radioButton_8->setText(QString());
        groupBox_3->setTitle(QApplication::translate("SideWidget", "GroupBox", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SideWidget", "Join existing patches", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SideWidget", "Merge existing patches", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("SideWidget", "Read Patch from file", Q_NULLPTR));
        read_btn->setText(QApplication::translate("SideWidget", "Insert patch", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("SideWidget", "Manipulate patch", Q_NULLPTR));
        select_shader->clear();
        select_shader->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "Two sided lighting", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Toonify", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Reflection lines", Q_NULLPTR)
        );
        select_material->clear();
        select_material->insertItems(0, QStringList()
         << QApplication::translate("SideWidget", "Brass", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Gold", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Silver", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Emerald", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Pearl", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Ruby", Q_NULLPTR)
         << QApplication::translate("SideWidget", "Turquoise", Q_NULLPTR)
        );
        label_10->setText(QApplication::translate("SideWidget", "Translate:", Q_NULLPTR));
        label_11->setText(QApplication::translate("SideWidget", "X", Q_NULLPTR));
        label_12->setText(QApplication::translate("SideWidget", "Y", Q_NULLPTR));
        label_13->setText(QApplication::translate("SideWidget", "Z", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
