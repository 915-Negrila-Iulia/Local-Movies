#pragma once
#include <qabstractitemmodel.h>
#include "../user_data/file_watch_list.h"

class MoviesTableModel : public QAbstractTableModel{

private:
    FileWatchList *watch_list;

public:
    MoviesTableModel(FileWatchList *wl): watch_list{wl}{};

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

};
