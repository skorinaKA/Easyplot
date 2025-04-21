#ifndef EASY_PLOT_HPP_INCLUDED
#define EASY_PLOT_HPP_INCLUDED

#include "main/easy_plot_common.hpp"
#include "main/easy_plot_line_spec.hpp"
#include "main/easy_plot_window_spec.hpp"
#include "main/easy_plot_draw.hpp"

namespace easy_plot {

    class EasyPlotTest {
    private:
        inline static WindowSpec default_window_style; /**< ����� ���� �� ��������� */

        static inline std::future<void> drawings_future;   /**< ��� ������������ ������ ��������� ����������� */
        static inline std::mutex drawings_mutex;           /**< ������� ��� ������ � ������� ����������� */

        class DrawingThreadTest {
        public:
            std::mutex drawings_mutex;          /**< ������� ��� ������ � ������� ����������� */
            std::future<void> drawings_future;   /**< ��� ������������ ������ ��������� ����������� */
            std::atomic<bool> is_shutdown = ATOMIC_VAR_INIT(false);

            DrawingThread() {};

            void init(int* argc, char* argv[]) {
            };

            ~DrawingThread() {
            };
        };

        static inline DrawingThread drawing_thread;

    public:
        using WindowSpec = easy_plot::WindowSpec;
        using LineSpec = easy_plot::LineSpec;
        //------------------------------------------------------------------------------
                /** \brief ���������������� ������ � ���������
                 * \param argc �������� ��������� ������
                 * \param argv �������� ��������� ������
                 */
        static void init(int* argc, char* argv[]) {
        }
        //------------------------------------------------------------------------------
        static int get_pos_plot(const std::string& name) {
            using namespace tools;
            for (size_t i = 0; i < Drawing::drawings.size(); ++i) {
                if (Drawing::drawings[i]->window_name == name) return i;
            }
            return -1;
        }
        //------------------------------------------------------------------------------
                /** \brief C����� ��������� ��������, ��������� ���������� ��� ��� ���� �����
                 * \param name ��� ����
                 * \param wstyle ����� ����
                 * \param count ���������� �������� � ������
                 * \param ... ������������ �������� � ������ �� ������� (y2, style2, y3, style2 � �.�.)
                 * \return ��������� ������, 0 � ������ ������, ����� ��. TypesErrors
                 */
        template <typename T1>
        static int plot(const std::string& name, const WindowSpec& wstyle, const size_t count, ...) {
            using namespace tools;
            va_list va;
            va_start(va, count);

            std::vector<std::vector<T1>> data;
            std::vector<LineSpec> line_style;
            for (size_t n = 0; n < count; ++n) {
                std::vector<T1> vec_next = va_arg(va, std::vector<T1>);
                LineSpec style_next = va_arg(va, LineSpec);
                data.push_back(vec_next);
                line_style.push_back(style_next);
            }
            va_end(va);

            {
                std::lock_guard<std::mutex> lock(drawings_mutex);
                int pos = get_pos_plot(name);
                if (pos >= 0) {
                    Drawing::drawings[pos]->init(name, wstyle, data, line_style);
                }
                else {
                    Drawing::drawings.push_back(std::make_shared<Drawing>(name, wstyle, data, line_style));
                }
            }
            return EASY_PLOT_OK;
        }
        //------------------------------------------------------------------------------
                /** \brief C����� ��������� ��������, ��������� ������ ��� X � Y.(���� ���)
                */
                //template <typename T1, typename T2>
                //static int plot2(const std::string& name, const WindowSpec& wstyle, const std::vector<std::vector<T1>> x, const std::vector<std::vector<T2>> y, const std::vector<LineSpec>& style) {
                //    using namespace tools;
                //    {
                //        std::lock_guard<std::mutex> lock(drawings_mutex);
                //        int pos = get_pos_plot(name);
                //        if (pos >= 0) {
                //            Drawing::drawings[pos]->init(name, wstyle, x, y, style);
                //        }
                //        else {
                //            Drawing::drawings.push_back(std::make_shared<Drawing>(name, wstyle, x, y, style));
                //        }
                //    }
                //    return EASY_PLOT_OK;
                //}

                // ������ ���� ����� ��� � plot2, �� ������ ������ �� ����� ����������� �������� ����(���� ���)
        template <typename T1, typename T2>
        static int corelogram(const std::string& name, const WindowSpec& wstyle, const std::vector<std::vector<T1>> x, const std::vector<std::vector<T2>> y, const std::vector<LineSpec>& style) {
            using namespace tools;
            {
                std::lock_guard<std::mutex> lock(drawings_mutex);
                int pos = get_pos_plot(name);
                if (pos >= 0) {
                    Drawing::drawings[pos]->init(name, wstyle, x, y, style);
                }
                else {
                    Drawing::drawings.push_back(std::make_shared<Drawing>(name, wstyle, x, y, style));
                }
            }
            return EASY_PLOT_OK;
        }

        //------------------------------------------------------------------------------
                /** \brief C����� ��������� ��������, ��������� ������ ��������(���� ���)
                */
        template <typename T1>
        static int plot(const std::string& name, const WindowSpec& wstyle, const std::vector<std::vector<T1>> waves, const std::vector<LineSpec>& style) {
            using namespace tools;

            {
                std::lock_guard<std::mutex> lock(drawings_mutex);
                int pos = get_pos_plot(name);
                if (pos >= 0) {
                    Drawing::drawings[pos]->init(name, wstyle, waves, style);
                }
                else {
                    Drawing::drawings.push_back(std::make_shared<Drawing>(name, wstyle, waves, style));
                }
            }
            return EASY_PLOT_OK;
        }
        //------------------------------------------------------------------------------
                /** \brief ������� ���������� �������� ������ ������ � Y �� ��������� � ���������������� ���������� � X.
                 * ������� ������� ���������� Y ������ X,
                 * X � Y ������ ����� ���������� �����.
                 * \param name ��� ����
                 * \param wstyle ����� ����
                 * \param x ������ �� ��� X
                 * \param y ������ �� ��� Y
                 * \param style ����� �����
                 * \return ��������� ������, 0 � ������ ������, ����� ��. TypesErrors
                 */
        template <typename T1, typename T2>
        static int plot(const std::string& name, const WindowSpec& wstyle, const std::vector<T1>& x, const std::vector<T2>& y, const LineSpec& style = LineSpec()) {
            using namespace tools;
            if (x.size() != y.size()) return EASY_PLOT_INVALID_PARAMETR;

            std::lock_guard<std::mutex> lock(drawings_mutex);
            int pos = get_pos_plot(name);
            if (pos >= 0) {
                Drawing::drawings[pos]->init(name, wstyle, x, y, style);
            }
            else {
                Drawing::drawings.push_back(std::make_shared<Drawing>(name, wstyle, x, y, style));
            }
            return EASY_PLOT_OK;
        }
        //------------------------------------------------------------------------------
                /** \brief ������� ���������� �������� ������ ������ � Y �� ��������� � ���������������� ���������� � X.
                 * ������� ������� ���������� Y ������ X,
                 * X � Y ������ ����� ���������� �����.
                 * \param name ��� ����
                 * \param x ������ �� ��� X
                 * \param y ������ �� ��� Y
                 * \param style ����� �����
                 * \return ��������� ������, 0 � ������ ������, ����� ��. TypesErrors
                 */
        template <typename T1, typename T2>
        static int plot(const std::string& name, const std::vector<T1>& x, const std::vector<T2>& y, const LineSpec& style = LineSpec()) {
            return plot(name, default_window_style, x, y, style);
        }
        //------------------------------------------------------------------------------
                /** \brief ������� ���������� �������� ������ ������ � Y �� ��������� � �������� ������� ��������.
                 * \param name ��� ����
                 * \param wstyle ����� ����
                 * \param y ������ �� ��� Y
                 * \param style ����� �����
                 * \return ��������� ������, 0 � ������ ������, ����� ��. TypesErrors
                 */
        template <typename T1>
        static int plot(const std::string& name, const WindowSpec& wstyle, const std::vector<T1>& y, const LineSpec& style = LineSpec()) {
            using namespace tools;
            if (y.size() <= 1) return EASY_PLOT_INVALID_PARAMETR;
            std::lock_guard<std::mutex> lock(drawings_mutex);
            int pos = get_pos_plot(name);
            if (pos >= 0) {
                Drawing::drawings[pos]->init(name, wstyle, y, style);
            }
            else {
                Drawing::drawings.push_back(std::make_shared<Drawing>(name, wstyle, y, style));
            }
            return EASY_PLOT_OK;
        }
        //------------------------------------------------------------------------------
        template <typename T1>
        static int plot(const std::string& name, const std::vector<T1>& y, const LineSpec& style = LineSpec()) {
            return plot(name, default_window_style, y, style);
        }

        static void save_image(std::string window_name, std::string file_name) {
        }
        //------------------------------------------------------------------------------
        static int draw_heatmap(const std::string& name, const WindowSpec& wstyle, const float* image, const size_t width, const size_t height) {
            return EASY_PLOT_OK;
        }
        //------------------------------------------------------------------------------
    }; // EasyPlot
}; // easy_plot

using ep = easy_plot::EasyPlot;

#endif // EASY_PLOT_HPP_INCLUDED
