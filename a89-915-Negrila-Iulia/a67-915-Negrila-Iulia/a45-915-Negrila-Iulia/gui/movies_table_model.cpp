#include "movies_table_model.h"

int MoviesTableModel::rowCount(const QModelIndex &parent) const {

    return this->watch_list->get_movies().size();
}

int MoviesTableModel::columnCount(const QModelIndex &parent) const {
//columns-> title, year, genre
    return 3;
}

QVariant MoviesTableModel::data(const QModelIndex &index, int role) const {

    int row = index.row();
    int column = index.column();
    Movie current_movie = this->watch_list->get_movies()[row];

    if(role == Qt::DisplayRole){

        switch(column){
            case 0:
                return QString::fromStdString(current_movie.get_title());
            case 1:
                return QString::number(current_movie.get_year_of_release());
            case 2:
                return QString::fromStdString(current_movie.get_genre());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant MoviesTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if(role == Qt::DisplayRole)
        if(orientation == Qt::Horizontal)
            switch(section){
                case 0:
                    return QString("Title");
                case 1:
                    return QString("Year of release");
                case 2:
                    return QString("Genre");
                default:
                    break;
            }

    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags MoviesTableModel::flags(const QModelIndex &index) const {

    int column = index.column();
    if (column == 0)
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return Qt::ItemIsSelectable;
}

bool MoviesTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    return QAbstractItemModel::setData(index, value, role);
}


