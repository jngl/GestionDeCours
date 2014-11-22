#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>
#include <QItemSelection>

#include "Model/ProjectTree/tree.h"

#include "Model/factory.h"

namespace Ui {
class MainWindow;
}

namespace View
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        virtual ~MainWindow();

    public slots:
        void on_actionAjouterProjet_triggered();
        void on_actionAjouterCompetence_triggered();
        void on_actionAjouterActivites_triggered();

        void projectsTreeSelectionChange(const QItemSelection & selected,
                                         const QItemSelection & deselected);

        void on_tabWidget_currentChanged(int index);

        void on_inclureActivite_clicked();

    private:
        Ui::MainWindow *ui;

        QDataWidgetMapper *projectsMapper;

        Model::Factory mFactory;
    };
}

#endif // MAINWINDOW_H
