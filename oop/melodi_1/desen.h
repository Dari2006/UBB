#include "service.h"
#include <qwidget.h>
#include <qpainter.h>
class Desen : public QWidget {
	private:
		Service& s;
	public:
		Desen(Service& s) : s{ s } {

		}
	protected:
		void paintEvent(QPaintEvent* event) override {
			QPainter painter{this};
			painter.setPen(Qt::darkCyan);
			painter.setFont(QFont("Arial", 30));
			//painter.drawText(rect(), Qt::AlignCenter, "Qt");
			const auto& toate = s.getAll();
			vector<int> rank;
			rank.resize(11);
			for(int i{0}; i < 11; i++)
				rank[i]=0;
			for (const auto& m : toate) {
				++rank[m.getRank()];
			}
			int inaltime{2};
			int x{0};
			//painter.drawRect(1, 60, 20, 20);
			//painter.drawRect(20, 60, 20, 20);
			//int i{0};
			for (const auto& r : rank) {
				painter.drawRect(x, 60, 20, r * 20);
				//++i;
				x+=20;
			}
		}
};
