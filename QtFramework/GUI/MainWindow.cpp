#include "MainWindow.h"
#include "qsignalmapper.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

        connect(_side_widget->_select_img, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_img(int)));
        connect(_side_widget->_select_index, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_index(int)));

        // PROJEKT
        // patch beolvasasahoz spin file index valasztasra es button meghivasra
        connect(_side_widget->file_index_spin, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_file_index(int)));
        connect(_side_widget->read_btn, SIGNAL(released()), _gl_widget, SLOT(call_read_patch()));
        // patch kiiratasa fajlba
        connect(_side_widget->write_btn, SIGNAL(released()), _gl_widget, SLOT(call_write_patch()));
        // patch shader/mat valtoztatasahoz spin patch index valasztasra es combobox shader/mat index valasztasra
        connect(_side_widget->patch_index_spin, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_patch_index(int)));
        connect(_side_widget->select_shader, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_shader_index(int)));
        connect(_side_widget->select_material, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_material_index(int)));

        // iranyvalaszto radiogombok irany beallitasra
        QSignalMapper* signalMapper1 = new QSignalMapper(this);
        connect(_side_widget->rb_N_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_NE_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_E_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_SE_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_S_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_SW_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_W_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
        connect(_side_widget->rb_NW_1, SIGNAL(clicked()), signalMapper1, SLOT(map()));

        signalMapper1->setMapping(_side_widget->rb_N_1, 0);
        signalMapper1->setMapping(_side_widget->rb_NE_1, 1);
        signalMapper1->setMapping(_side_widget->rb_E_1, 2);
        signalMapper1->setMapping(_side_widget->rb_SE_1, 3);
        signalMapper1->setMapping(_side_widget->rb_S_1, 4);
        signalMapper1->setMapping(_side_widget->rb_SW_1, 5);
        signalMapper1->setMapping(_side_widget->rb_W_1, 6);
        signalMapper1->setMapping(_side_widget->rb_NW_1, 7);

        connect(signalMapper1, SIGNAL(mapped(int)), _gl_widget, SLOT(set_direction1(int)));

        QSignalMapper* signalMapper2 = new QSignalMapper(this);
        connect(_side_widget->rb_N_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_NE_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_E_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_SE_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_S_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_SW_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_W_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        connect(_side_widget->rb_NW_2, SIGNAL(clicked()), signalMapper2, SLOT(map()));

        signalMapper2->setMapping(_side_widget->rb_N_2, 0);
        signalMapper2->setMapping(_side_widget->rb_NE_2, 1);
        signalMapper2->setMapping(_side_widget->rb_E_2, 2);
        signalMapper2->setMapping(_side_widget->rb_SE_2, 3);
        signalMapper2->setMapping(_side_widget->rb_S_2, 4);
        signalMapper2->setMapping(_side_widget->rb_SW_2, 5);
        signalMapper2->setMapping(_side_widget->rb_W_2, 6);
        signalMapper2->setMapping(_side_widget->rb_NW_2, 7);

        connect(signalMapper2, SIGNAL(mapped(int)), _gl_widget, SLOT(set_direction2(int)));

        // extend/join/merge-hez patchek indexeit beallito
        connect(_side_widget->patch1_index_spin, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_patch1_index(int)));
        connect(_side_widget->patch2_index_spin, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_patch2_index(int)));
        // gombok ezekhez ^
        connect(_side_widget->extend_btn, SIGNAL(released()), _gl_widget, SLOT(call_extend_patch()));
        connect(_side_widget->extend_new_btn, SIGNAL(released()), _gl_widget, SLOT(call_extend_new_patch()));
        connect(_side_widget->join_btn, SIGNAL(released()), _gl_widget, SLOT(call_join_patch()));
        connect(_side_widget->merge_btn, SIGNAL(released()), _gl_widget, SLOT(call_merge_patch()));

        // translacio x, y, z iranyokba
        connect(_side_widget->plus_X_btn, SIGNAL(pressed()), _gl_widget, SLOT(plus_X()));
        connect(_side_widget->minus_X_btn, SIGNAL(pressed()), _gl_widget, SLOT(minus_X()));
        connect(_side_widget->plus_Y_btn, SIGNAL(pressed()), _gl_widget, SLOT(plus_Y()));
        connect(_side_widget->minus_Y_btn, SIGNAL(pressed()), _gl_widget, SLOT(minus_Y()));
        connect(_side_widget->plus_Z_btn, SIGNAL(pressed()), _gl_widget, SLOT(plus_Z()));
        connect(_side_widget->minus_Z_btn, SIGNAL(pressed()), _gl_widget, SLOT(minus_Z()));

        //egy sarok vektorertekeinek valtoztatasai - (x,y,z)

        connect(_side_widget->_corners_cb, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_corners_index(int)));
        connect(_side_widget->_vectors_cb, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_vectors_index(int)));

        connect(_side_widget->_xValue_tb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_xValue_changed(double)));
        connect(_side_widget->_yValue_tb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_yValue_changed(double)));
        connect(_side_widget->_zValue_tb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_zValue_changed(double)));

        connect(_side_widget->_change_bt, SIGNAL(pressed()), _gl_widget, SLOT(_change_bt_clicked()));

    }


    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
