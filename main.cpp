#include <iostream>
#include <cmath>
#include <cassert>
#include "easy_plot.hpp"

using namespace std;


void Test_print_screen_1() {
    easy_plot::utility::Screenshot screen;
    screen.print_screen("screen1.png", 640, 480, easy_plot::utility::Screenshot::TypesFormats::USE_PPM);
}

void Test_print_screen_2() {
    easy_plot::utility::Screenshot screen;
    screen.print_screen("screen2.ppm", 640, 480, easy_plot::utility::Screenshot::TypesFormats::USE_PPM);
}

void Test_print_screen_3() {
    easy_plot::utility::Screenshot screen;
    screen.print_screen("screen3.ppm", 320, 240, easy_plot::utility::Screenshot::TypesFormats::USE_PPM);
}

void Test_init_1(int* argc, char** argv) {
    ep::init(argc, argv);
}

void Test_init_2(int* argc, char** argv) {
    *argc = 0;
    ep::init(argc, argv);
    *argc = 1;
    ep::init(argc, argv);
}

void Test_get_pos_plot_1() {
    std::string name = "Test";
    int res = easy_plot::EasyPlot::get_pos_plot(name);
    std::cout << "result of get_pos_plot: " << res << std::endl;
    assert(res == -1);
}

void Test_get_pos_plot_2() {

}

void Test_plot_1() {

}

void Test_plot_2() {

}

void Test_plot_3() {

}

void Test_plot_4() {

}


void Test_draw_heatmap_3(){
    ep::WindowSpec image_wstyle;
    image_wstyle.is_grid = true;
    image_wstyle.height = 320;
    image_wstyle.width = 320;
    float image_data[32][32] = {};
    size_t image_ind = 0;
    for (size_t x = 0; x < 32; ++x) {
        for (size_t y = 0; y < 32; ++y, ++image_ind) {
            image_data[x][y] = 1024 - std::sqrt((x - 18) * (x - 18) + (y - 18) * (y - 18));
        }
    }
    image_wstyle.is_color_heatmap = false;
    int res = ep::draw_heatmap("image_heatmap", image_wstyle, &image_data[0][0], 32, 32);
    assert(res == 0);
    image_wstyle.is_color_heatmap = true;
    res = ep::draw_heatmap("image_heatmap_color", image_wstyle, &image_data[0][0], 32, 32);
    assert(res == 0);
    image_wstyle.is_color_heatmap = true;
    image_wstyle.is_invert_color_heatmap = true;
    res = ep::draw_heatmap("image_heatmap_invert_color", image_wstyle, &image_data[0][0], 32, 32);
    assert(res == 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void EasyPlot(int *argc, char **argv)
{
    ep::init(argc, argv);
    cout << "Hello plot!" << endl;


    ep::WindowSpec wstyle0;
    wstyle0.is_zero_x_line = true;
    wstyle0.is_zero_y_line = true;
    std::vector<double> test1_x = { 1.2,1,1,1,1.2,1,1 };
    int res = ep::plot("test1", wstyle0, test1_x);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    assert(res == 0);

    //ep::WindowSpec wstyle0;
    wstyle0.is_zero_x_line = true;
    wstyle0.is_zero_y_line = true;
    std::vector<double> test2_x = { 0,2,3,4,2,0,1 };
    res = ep::plot("test2", test2_x);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    assert(res == 0);

    easy_plot::utility::Screenshot screen;
    screen.print_screen("screen3.ppm", 320, 240, easy_plot::utility::Screenshot::TypesFormats::USE_PPM);

    ep::WindowSpec wstyle3;
    wstyle3.is_zero_x_line = true;
    wstyle3.is_zero_y_line = true;
    test2_x = { 0,2,3,4,2,0,1 };
    std::vector<double> test3_x = { -2,2,6,7,8,10,12 };
    res = ep::plot("test3", wstyle3, test3_x, test2_x, ep::LineSpec(1, 1, 0));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    assert(res == 0);
    
    std::vector<double> test1_xx;
    for (int i = 0; i < 2000; ++i) {
        test1_xx.push_back(i % 53);
    }
    ep::WindowSpec wstyle_xx;
    wstyle_xx.grid_period = 2.0 / 24.0;
    res = ep::plot<double>("test1-1", wstyle_xx, (int)1, test1_xx, ep::LineSpec(1, 0, 0));
    res = ep::plot<double>("test1-2", wstyle_xx, (int)1, test1_xx, ep::LineSpec(0, 1, 0));
    res = ep::plot<double>("test1-3", wstyle_xx, (int)1, test1_xx, ep::LineSpec(0, 0, 1));
    res = ep::plot<double>("test1-4", wstyle_xx, (int)1, test1_xx, ep::LineSpec(0, 1, 1));

    ep::WindowSpec wstyle;
    wstyle.grid_period = 2.0 / 24.0;
    ep::plot<double>("test4", wstyle, (int)3, test1_x, ep::LineSpec(1, 0, 0), test2_x, ep::LineSpec(1, 0, 1), test3_x, ep::LineSpec(0, 1, 0));
    ep::save_image("test4", "test4.ppm");

    std::vector<double> line;
    for (int i = 0; i < 500; ++i) {
        line.push_back(sin(3.1415 * (double)i / 50));
    }
    std::vector<double> line05(line.size(), 0.5);
    std::vector<double> line06(line.size(), 0.6);
    ep::WindowSpec wstyle2;
    wstyle2.grid_period = 2.0 / 24.0;
    res = ep::plot<double>("test5", wstyle2, (int)3,
        line, ep::LineSpec(1, 0, 0),
        line05, ep::LineSpec(1, 0, 1),
        line06, ep::LineSpec(0, 1, 0));

    ep::save_image("qwerty", "testwave999.ppm");
    ep::save_image("test5", "test5.ppm");
    wstyle2.is_zero_x_line = true;

    // нарисуем изображение


    // продолжим обновлять график
    int count = 10;
    std::vector<std::vector<double>> waves1x(count);
    std::vector<std::vector<double>> waves2x(count);
    std::vector<std::vector<double>> waves3x(count);
    std::vector<std::vector<double>> waves1y(count);
    std::vector<std::vector<double>> waves2y(count);
    std::vector<std::vector<double>> waves3y(count);
    std::vector<ep::LineSpec> line_style1, line_style2, line_style3;
    for (int size = 0; size < count; size++) {
        for (int i = 0; i < 50; ++i) {
            if (i % 2 == 0) {
                waves1y[size].push_back(1 + size * 2);
                waves1y[size].push_back(0 + size * 2);
                waves2y[size].push_back(0 + size * 2);
                waves2y[size].push_back(1 + size * 2);
                waves3y[size].push_back(1 + size * 2);
                waves3y[size].push_back(0 + size * 2);
            }
            else {
                waves1y[size].push_back(0 + size * 2);
                waves1y[size].push_back(1 + size * 2);
                waves2y[size].push_back(1 + size * 2);
                waves2y[size].push_back(0 + size * 2);
                waves3y[size].push_back(0 + size * 2);
                waves3y[size].push_back(1 + size * 2);
            }
            waves1x[size].push_back(i);
            waves1x[size].push_back(i);
            waves2x[size].push_back(i);
            waves2x[size].push_back(i);
            waves3x[size].push_back(i);
            waves3x[size].push_back(i);
        }
        line_style1.push_back(ep::LineSpec(1, 0, 0));
        line_style2.push_back(ep::LineSpec(0, 1, 0));
        line_style3.push_back(ep::LineSpec(1, 0, 1));
    }
    ep::WindowSpec wave1;
    wave1.is_zero_x_line = true;
    wave1.is_zero_y_line = true;
    ep::WindowSpec wave2;
    wave2.is_zero_x_line = true;
    wave2.is_zero_y_line = true;
    wave1.height = 600;
    wave1.width = 800;
    wave1.grid_period = 2.0 / 24.0;
    ep::corelogram("testwave", wave1, waves1x, waves1y, line_style1);
    ep::corelogram("testwave2", wave1, waves2x, waves2y, line_style2);
    ep::corelogram("testwave3", wave1, waves3x, waves3y, line_style3);
    ep::save_image("qwerty", "testwave999.ppm");
    ep::save_image("testwave", "");
    ep::save_image("testwave", "testwave.ppm");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    //////////////////////////////////////////////////////////////

    std::vector<double> wav1x;
    std::vector<double> wav1y;
    std::vector<double> wav2x;
    std::vector<double> wav2y;
    for (int i = 0; i < 50; ++i) {
        if (i % 2 == 0) {
            wav1y.push_back(1);
            wav1y.push_back(0);
            wav2y.push_back(0);
            wav2y.push_back(1);
        }
        else {
            wav1y.push_back(0);
            wav1y.push_back(1);
            wav2y.push_back(1);
            wav2y.push_back(0);
        }
        wav1x.push_back(i);
        wav1x.push_back(i);
        wav2x.push_back(i);
        wav2x.push_back(i);
    }
    //ep::WindowSpec wave1;
    wave1.is_zero_x_line = true;
    wave1.is_zero_y_line = true;
    wave1.height = 200;
    wave1.width = 1800;
    wave1.grid_period = 2.0 / 24.0;
    //ep::WindowSpec wave2;
    wave2.is_zero_x_line = true;
    wave2.is_zero_y_line = true;
    wave2.height = 200;
    wave2.width = 1800;
    ep::plot<double>("testwave", wave1, wav1x, wav1y, ep::LineSpec(1, 0, 0));
    ep::plot<double>("testwave2", wave2, wav2x, wav2y, ep::LineSpec(1, 0, 1));
    ep::plot<double>("testwave3", wave2, wav2x, wav2y, ep::LineSpec(0, 0, 1));

    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ep::plot<double>("testwave", wave2, wav2x, wav2y, ep::LineSpec(1, 0, 1));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ep::plot<double>("testwave", wave1, wav1x, wav1y, ep::LineSpec(1, 0, 0));
    }

    screen.print_screen("screen3.ppm", 320, 240, easy_plot::utility::Screenshot::TypesFormats::USE_PPM);

    //std::vector<double> wav1x;
    //std::vector<double> wav1y;
    //std::vector<double> wav2x;
    //std::vector<double> wav2y;
    count = 10;
    std::vector<std::vector<double>> waves1(count);
    std::vector<std::vector<double>> waves2(count);
    std::vector<std::vector<double>> waves3(count);
    //std::vector<ep::LineSpec> line_style1,line_style2,line_style3;
    for (int size = 0; size < count; size++) {
        for (int i = 0; i < 500000; ++i) {
            if ((i / 20000) % 2 == 0) {
                waves1[size].push_back(1 + size * 2);
                waves2[size].push_back(0 + size * 2);
                waves3[size].push_back(1 + size * 2);
            }
            else {
                waves1[size].push_back(0 + size * 2);
                waves2[size].push_back(1 + size * 2);
                waves3[size].push_back(0 + size * 2);
            }
        }
        line_style1.push_back(ep::LineSpec(1, 0, 0));
        line_style2.push_back(ep::LineSpec(0, 1, 0));
        line_style3.push_back(ep::LineSpec(1, 0, 1));
    }

    //ep::WindowSpec wave1;
    wave1.is_zero_x_line = true;
    wave1.is_zero_y_line = true;
    wave1.height = 900;
    wave1.width = 1200;
    ep::plot<double>("testwave", wave1, waves1, line_style1);
    ep::plot<double>("testwave2", wave1, waves2, line_style2);
    ep::plot<double>("testwave3", wave1, waves3, line_style3);



    // увеличим выборку и будем перерисовывать график некоторое время
    //for (int step = 0; step < 1000; step++) {
    //    std::vector<double> line;
    //    for (int i = 0; i < 1000; ++i) {
    //        line.push_back(sin(3.1415 * (double)(i + step * 10) / 50));
    //    }
    //    std::vector<double> line05(line.size(), -0.5);
    //    std::vector<double> line06(line.size(), 0.6);
    //    ep::plot<double>("test5", wstyle2, 3,
    //        line, ep::LineSpec(1, 0, 0),
    //        line05, ep::LineSpec(1, 0, 1),
    //        line06, ep::LineSpec(0, 1, 0));
    //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //}

    //while(true) {
    //    std::this_thread::yield();
    //}
}

int main(int argc, char* argv[]) {

    if (argc > 1)
    {
        int switch_on = std::atoi(argv[1]);
        switch (switch_on)
        {
        case 1:
            Test_print_screen_1();
            Test_print_screen_2();
            Test_print_screen_3();
            break;
        case 2:
            Test_init_1(&argc, argv);
            //Test_init_2(&argc, argv);
            break;
        case 3:
            Test_get_pos_plot_1();
            break;
        case 4:
            ep::init(&argc, argv);
            Test_plot_1();
            Test_plot_2();
            Test_plot_3();
            EasyPlot(&argc, argv);
            break;
        case 7:
            Test_draw_heatmap_3();
        default:
            EasyPlot(&argc, argv);
            break;
        }
        return 0;
    }

    EasyPlot(&argc, argv);
    cin.get();

    return 0;
}
