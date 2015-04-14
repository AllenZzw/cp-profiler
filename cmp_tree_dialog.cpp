#include "cmp_tree_dialog.hh"
#include "nodewidget.hh"
#include "treecomparison.hh"

#include <utility> // pair

CmpTreeDialog::CmpTreeDialog(ReceiverThread* receiver, const CanvasType type, Gist* gist,
                             TreeCanvas* tc1, TreeCanvas* tc2)
: BaseTreeDialog(receiver, type, gist),
_comparison{new TreeComparison()}, analysisMenu{nullptr}, pentListWindow{this} {

  hbl->addWidget(new NodeWidget(MERGING));
  mergedLabel = new QLabel("0");
  hbl->addWidget(mergedLabel);

  addActions();

  nodeMenu->addAction(_navFirstPentagon);
  nodeMenu->addAction(_navNextPentagon);
  nodeMenu->addAction(_navPrevPentagon);
  connect(_navFirstPentagon, SIGNAL(triggered()), this, SLOT(navFirstPentagon()));
  connect(_navNextPentagon, SIGNAL(triggered()), this, SLOT(navNextPentagon()));
  connect(_navPrevPentagon, SIGNAL(triggered()), this, SLOT(navPrevPentagon()));

  analysisMenu = menuBar->addMenu(tr("&Analysis"));
  analysisMenu->addAction(_showPentagonHist);
  connect(_showPentagonHist, SIGNAL(triggered()), this, SLOT(showPentagonHist()));


  _comparison->compare(tc1, tc2, _tc);

  mergedLabel->setNum(_comparison->get_no_pentagons());
  statusChangedShared(true);

}

void
CmpTreeDialog::addActions(void) {
  _navFirstPentagon = new QAction("To first pentagon", this);
  _navFirstPentagon->setShortcut(QKeySequence("Ctrl+Shift+1"));

  _navNextPentagon = new QAction("To next pentagon", this);
  _navNextPentagon->setShortcut(QKeySequence("Ctrl+Shift+Right"));

  _navPrevPentagon = new QAction("To prev pentagon", this);
  _navPrevPentagon->setShortcut(QKeySequence("Ctrl+Shift+Left"));

  _showPentagonHist = new QAction("Pentagon list", this);

  addAction(_navFirstPentagon);
  addAction(_navNextPentagon);
  addAction(_navPrevPentagon);
}

CmpTreeDialog::~CmpTreeDialog(void) {
  delete _comparison;
}

void
CmpTreeDialog::statusChanged(VisualNode*, const Statistics& stats, bool finished) {

  statusChangedShared(finished);

}

void
CmpTreeDialog::navFirstPentagon(void) {
  const std::vector<VisualNode*>& pentagons = _comparison->pentagons();

  if (pentagons.size() == 0) {
    qDebug() << "warning: pentagons.size() == 0";
    return;
  }

  _tc->setCurrentNode(pentagons[0]);
  _tc->centerCurrentNode();

}

void
CmpTreeDialog::navNextPentagon(void) {

  _tc->navNextPentagon();

}

void
CmpTreeDialog::navPrevPentagon(void) {

  _tc->navNextPentagon(true);
}

void
CmpTreeDialog::showPentagonHist(void) {
  pentListWindow.createList(_comparison->pentagons(), _comparison->pentSize());
  pentListWindow.show();
}

/// *************** Pentagon List Window ****************

PentListWindow::PentListWindow(QWidget* parent)
: QDialog(parent), _histTable{this} {

  resize(600, 400);

  connect(&_histTable, SIGNAL(cellDoubleClicked (int, int)), parent, SLOT(selectPentagon(int, int)));
  QHBoxLayout* layout = new QHBoxLayout(this);

  // QStringList table_header;
  // table_header << "#" << "Left" << "Right";
  // _histTable.setHorizontalHeaderLabels(table_header);

  _histTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
  _histTable.setSelectionBehavior(QAbstractItemView::SelectRows);

  layout->addWidget(&_histTable);
}

void
PentListWindow::createList(const std::vector<VisualNode*>& pentagons,
                           const std::vector<std::pair<unsigned int, unsigned int>>& pentSize)
{
 
  // p_pentagons = &pentagons;

  _histTable.setColumnCount(2);
  _histTable.setRowCount(pentagons.size());

  for (unsigned int i = 0; i < pentagons.size(); i++) {
    _histTable.setItem(i, 0, new QTableWidgetItem(QString::number(pentSize[i].first)));
    _histTable.setItem(i, 1, new QTableWidgetItem(QString::number(pentSize[i].second)));
  }
  
}

void
CmpTreeDialog::selectPentagon(int row, int) {
  const std::vector<VisualNode*>& pentagons = _comparison->pentagons();

  _tc->setCurrentNode(pentagons[row]);
  _tc->centerCurrentNode();
}

/// ******************************************************