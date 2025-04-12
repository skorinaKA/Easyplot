#ifndef EASY_PLOT_WINDOW_SPEC_HPP_INCLUDED
#define EASY_PLOT_WINDOW_SPEC_HPP_INCLUDED

namespace easy_plot {

    class WindowSpec {
        public:
        uint32_t width = EASY_PLOT_DEF_WIDTH;      
        uint32_t height = EASY_PLOT_DEF_HEIGHT;    
        double indent = EASY_PLOT_DEF_INDENT;      
        double indent_frame = EASY_PLOT_DEF_INDENT;

        // цвет изображения
        double ir = 1.0;
        double ig = 1.0;
        double ib = 1.0;

        // цвет фона
        double br = 0.0;
        double bg = 0.0;
        double bb = 0.0;

        // цвет сетки
        double gr = 0.1;
        double gg = 0.1;
        double gb = 0.1;

        // цвет рамки
        double fr = 1.0;
        double fg = 1.0;
        double fb = 1.0;

        // цвет текста
        double tr = 1.0;
        double tg = 1.0;
        double tb = 1.0;

        // цвет указател
        double mr = 0.5;
        double mg = 0.5;
        double mb = 0.5;

        bool is_zero_x_line = false;         
        bool is_zero_y_line = false;         
        bool is_grid = true;                 
        bool is_color_heatmap = true;        
        bool is_invert_color_heatmap = false;
        double grid_period = 0.1;            

        void *font = GLUT_BITMAP_8_BY_13;    

        WindowSpec() {};
    };

}; // easy_plot

#endif // EASY_PLOT_WINDOW_SPEC_HPP_INCLUDED
