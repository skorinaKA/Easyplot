#ifndef EASY_PLOT_LINE_SPEC_HPP_INCLUDED
#define EASY_PLOT_LINE_SPEC_HPP_INCLUDED

namespace easy_plot {

    class LineSpec {
        public:
        double r = 0.0, g = 1.0, b = 1.0, a = 1.0;
        LineSpec() {};

        LineSpec(double red, double green, double blue, double alpha = 1.0) {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }
    };

}; // easy_plo

#endif // EASY_PLOT_LINE_SPEC_HPP_INCLUDED
