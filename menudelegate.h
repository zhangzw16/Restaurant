#ifndef MENUDELEGATE_H
#define MENUDELEGATE_H

#include <QModelIndex>
#include <QPixmap>
#include <QSize>
#include <QSqlRelationalDelegate>

QT_FORWARD_DECLARE_CLASS(QPainter)

class MenuDelegate : public QSqlRelationalDelegate
{
public:
    MenuDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    QPixmap star;
    int StarColum;
};

#endif // MENUDELEGATE_H
