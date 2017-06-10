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

        // curve extend, merge es join parancsok extend_btn_2
        connect(_side_widget->curve1_index_spin, SIGNAL(valueChanged(int)), _gl_widget, SLOT(curve1_index_spin_changed(int)));
        connect(_side_widget->curve2_index_spin, SIGNAL(valueChanged(int)), _gl_widget, SLOT(curve2_index_spin_changed(int)));
        connect(_side_widget->dir1_combo, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(direction1_combo_changed(int)));
        connect(_side_widget->dir2_combo, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(direction2_combo_changed(int)));
        connect(_side_widget->extend_btn_2, SIGNAL(pressed()), _gl_widget, SLOT(call_extend_curve()));
        connect(_side_widget->merge_btn_2, SIGNAL(pressed()), _gl_widget, SLOT(call_merge_curve()));
        connect(_side_widget->join_btn_2, SIGNAL(pressed()), _gl_widget, SLOT(call_join_curve()));
        //egy arc kivalasztott vektorjanak mozgatasa
        connect(_side_widget->select_arc_vector, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_arc_vector_index(int)));
        connect(_side_widget->select_vector_nr, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_vector_nr_index(int)));

        connect(_side_widget->arc_vector_plusX, SIGNAL(pressed()), _gl_widget, SLOT(arc_vector_plus_X()));
        connect(_side_widget->arc_vector_plusY, SIGNAL(pressed()), _gl_widget, SLOT(arc_vector_plus_Y()));
        connect(_side_widget->arc_vector_plusZ, SIGNAL(pressed()), _gl_widget, SLOT(arc_vector_plus_Z()));
        connect(_side_widget->arc_vector_minusX, SIGNAL(pressed()), _gl_widget, SLOT(arc_vector_minus_X()));
        connect(_side_widget->arc_vector_minusY, SIGNAL(pressed()), _gl_widget, SLOT(arc_vector_minus_Y()));
        connect(_side_widget->arc_vector_minusZ, SIGNAL(pressed()), _gl_widget, SLOT(arc_vector_minus_Z()));
        // CURVES ---------- MANIPULATE ---------------------
        //_sp_curve -> the index of the curve (spin box)
        connect(_side_widget->_sp_curve, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_of_curve(int)));
        //_pb_Y_up, _pb_Y_down -> move selected curve upward and downward (Y)
        connect(_side_widget->_pb_Y_up, SIGNAL(pressed()), _gl_widget, SLOT(set_pb_Y_up()));
        connect(_side_widget->_pb_Y_down, SIGNAL(pressed()), _gl_widget, SLOT(set_pb_Y_down()));
        //_pb_X_up, _pb_X_down -> move selected curve upward and downward (X)
        connect(_side_widget->_pb_X_up, SIGNAL(pressed()), _gl_widget, SLOT(set_pb_X_up()));
        connect(_side_widget->_pb_X_down, SIGNAL(pressed()), _gl_widget, SLOT(set_pb_X_down()));
        //_pb_Z_up, _pb_Z_down -> move selected curve upward and downward (Z)
        connect(_side_widget->_pb_Z_up, SIGNAL(pressed()), _gl_widget, SLOT(set_pb_Z_up()));
        connect(_side_widget->_pb_Z_down, SIGNAL(pressed()), _gl_widget, SLOT(set_pb_Z_down()));
        // color double spin box : _dsp_R, _dsp_G, _dsp_B
        connect(_side_widget->_dsp_R, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_R(double)));
        connect(_side_widget->_dsp_G, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_G(double)));
        connect(_side_widget->_dsp_B, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_B(double)));
        // _btn_Color
        connect(_side_widget->_btn_Color, SIGNAL(pressed()), _gl_widget, SLOT(set_curve_color()));

        //curve kiirasa a file-ba
        connect(_side_widget->write_curve_btn, SIGNAL(released()), _gl_widget, SLOT(call_write_curve()));
        //DERIVATIVES _cb_der1 _cb_der2
        connect(_side_widget->_cb_der1,SIGNAL(clicked(bool)),_gl_widget,SLOT(set_der1(bool)) );
        connect(_side_widget->_cb_der2,SIGNAL(clicked(bool)),_gl_widget,SLOT(set_der2(bool)) );


    }


    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
