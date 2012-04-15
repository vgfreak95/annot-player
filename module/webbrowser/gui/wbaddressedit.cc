// wbaddressedit.cc
// 3/31/2012

#include "wbaddressedit.h"
#include "wbss.h"
#include "ac/acrc.h"
#include "module/mrlanalysis/mrlanalysis.h"
#include <QtGui>

// - Construction -

void
WbAddressEdit::createActions()
{
  pasteAndGoAct = new QAction(this); {
    pasteAndGoAct->setText(tr("Paste and go"));
    pasteAndGoAct->setStatusTip(tr("Paste and go"));
    connect(pasteAndGoAct, SIGNAL(triggered()), SLOT(pasteAndGo()));
  }
  openAddressWithAcPlayerAct_ = new QAction(this); {
    openAddressWithAcPlayerAct_->setIcon(QIcon(ACRC_IMAGE_PLAYER));
    openAddressWithAcPlayerAct_->setText(tr("Play with Annot Player"));
    openAddressWithAcPlayerAct_->setStatusTip(tr("Open with Annot Player"));
    connect(openAddressWithAcPlayerAct_, SIGNAL(triggered()), SLOT(openAddressWithAcPlayer()));
  }
  openAddressWithAcDownloaderAct_ = new QAction(this); {
    openAddressWithAcDownloaderAct_->setIcon(QIcon(ACRC_IMAGE_DOWNLOADER));
    openAddressWithAcDownloaderAct_->setText(tr("Download with Annot Downloader"));
    openAddressWithAcDownloaderAct_->setStatusTip(tr("Open with Annot Downloader"));
    connect(openAddressWithAcDownloaderAct_, SIGNAL(triggered()), SLOT(openAddressWithAcDownloader()));
  }
}

// - Actions -

void
WbAddressEdit::pasteAndGo()
{
  QClipboard *c = QApplication::clipboard();
  if (c) {
    QString url = c->text().trimmed();
    if (!url.isEmpty())
      emit textEntered(url);
  }
}

bool
WbAddressEdit::isClipboardEmpty()
{
  QClipboard *c = QApplication::clipboard();
  return !c || c->text().trimmed().isEmpty();
}

// - Events -

void
WbAddressEdit::contextMenuEvent(QContextMenuEvent *event)
{
  if (!event)
    return;

  QMenu m;

  if (MrlAnalysis::matchSite(currentText().trimmed(), false)) { // href = false
    m.addAction(openAddressWithAcPlayerAct_);
    m.addAction(openAddressWithAcDownloaderAct_);
    m.addSeparator();
  }

  m.addAction(pasteAndGoAct);
  m.addAction(popupAct);
  m.addAction(clearAct);
  m.addSeparator();

  pasteAndGoAct->setEnabled(!isClipboardEmpty());
  popupAct->setEnabled(count());

  QMenu *scm = lineEdit()->createStandardContextMenu();
  m.addActions(scm->actions());

  m.exec(event->globalPos());
  delete scm;
  event->accept();
}

// EOF

/*
void
WbAddressEdit::keyPressEvent(QKeyEvent *event)
{
  Q_ASSERT(event);
  // Do not pass escape key to parent.
  switch (event->key()) {
  case Qt::Key_Escape:
    DOUT("Key_Escape");
    clearFocus();    // FIXME: after clear focus, which window get new focus?
    event->accept();
    return;

  case Qt::Key_Return:
    DOUT("Key_Return");
    event->accept();
    //emit returnPressed();
    return;

  case Qt::Key_Up:
    DOUT("Key_Up");
    //previous();
    event->accept();
    return;

  case Qt::Key_Down:
    DOUT("Key_Down");
    //next();
    event->accept();
    return;
  }
  Base::keyPressEvent(event);
}
*/