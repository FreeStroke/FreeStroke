/*
* Projet de fin d'études LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aurèle Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Université Paris-Est Marne-la-Vallée
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
/*!
 * \file listview.h
 * \brief The ListView class hold all the component of the list view of the application. It display a List of all the Gesture
 * and allow to modify them.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "glview/glview.h"
#include "element/button/buttonelement.h"
#include "../../includes/ui/gesturelistview/gesturelistview.h"
#include "../../includes/daolayer/daolayer.h"
#include "../../includes/ui/element/switcher/switcher.h"
#include "../../includes/ui/gestureparams/gestureparams.h"
#include "../../includes/ui/stepper/stepper.h"
#include "../../includes/ui/element/keylistener/keylistener.h"
#include "../../includes/ui/element/textfield/textfield.h"
#include "../../includes/ui/commandchooser/commandchooser.h"
#include "../../includes/ui/bottombar/bottombar.h"



/*!
 * \brief The ListView class hold all the component of the list view of the application. It display a List of all the Gesture
 * and allow to modify them.
 */
class ListView : public QWidget
{
     Q_OBJECT
public:
    /*!
     * \brief default ListView constructor
     * \param parent the container QWidget parent
     */
    ListView(QWidget *parent = 0);
    /*!
     * \brief getGestureListView returns the GestureListView of the ListView
     * \return the GestureListView of the ListView
     */
    GestureListView *getGestureListView();

private:
    /*!
     * \brief create the view
     */
    void createView();
    /*!
     * \brief reference to the gesture viewer
     */
    GlView * glView;
    /*!
     * \brief gestureListView the GestureListView holding all the Gesture
     */
    GestureListView* gestureListView;
    /*!
     * \brief ButtonElement changing the GLView between pause and play state
     */
    ButtonElement *btnPause;
    /*!
     * \brief rightLabel is the Label which display the number of Gesture selected in the GestureListView. Visible only
     * when 0 or more than 1 Gesture are selected
     */
    Label* rightLabel;
    /*!
     * \brief dao the DAOLayer
     */
    DAOLayer* dao;
    /*!
     * \brief switcherGesture the Switcher defining if a Gesture is active or not
     */
    Switcher *switcherGesture;
    /*!
     * \brief switcherAction the Switcher defining if a Gesture action is active or not
     */
    Switcher *switcherAction;
    /*!
     * \brief btnAdd ButtonElement used to add Gesture
     */
    ButtonElement *btnAdd;
    /*!
     * \brief btnTrash ButtonElement used to remove Gesture
     */
    ButtonElement *btnTrash;
    /*!
     * \brief btnExport ButtonElement used to export Gesture
     */
    ButtonElement *btnExport;
    /*!
     * \brief btnImport ButtonElement used to import Gesture
     */
    ButtonElement *btnImport;
    /*!
     * \brief params the GestureParam which hold ButtonElement and Switcher which have an impact on the selected Gesture
     */
    GestureParams* params;
    /*!
     * \brief labels the QWidget containing the Label visible when there are no Gesture in the GestureListView
     */
    QWidget* labels;
    /*!
     * \brief commandChooser the CommandChooser used to visualize and modify the Command of the selected Gesture
     */
    CommandChooser* commandChooser;
    /*!
     * \brief bottomRightBar the BottomBar containing the Element of the CommandChooser
     */
    BottomBar* bottomRightBar;
private slots:
    /*!
     * \brief deleteGestures slot called when deleting Gesture with the btnTrash. It remove the Gesture from the List and the DAOLayer
     */
    void deleteGestures();
    /*!
     * \brief addGesture slot called when adding Gesture with the btnAdd. It show the StepperNewGesture
     */
    void addGesture();
    /*!
     * \brief toggleGestureAnimation slot called when playing / pausing the animation of the GLView with the ButtonElement.
     */
    void toggleGestureAnimation();
    /*!
     * \brief refreshSelection slot called when the selection of the GestureListView has changed. It show or hide the GLView depending on
     * then number of Gesture selected (hide when 0 or >1).
     */
    void refreshSelection();
    /*!
     * \brief toogleActionState slot called when modifying the action state of a Gesture with the switcherAction. It updates
     * the DAOLayer.
     */
    void toogleActionState(bool);
    /*!
     * \brief toogleGestureState slot called when modifying the state of a Gesture with the switcherAction. It updates
     * the DAOLayer.
     */
    void toogleGestureState(bool);
    /*!
     * \brief toogleImport slot called when importing Gesture with the btnImport. It show a Stepper for each Gesture to import in
     * the choosen file.
     */
    void toogleImport();
    /*!
     * \brief toogleExport slot called when exporting Gesture with the btnExport. It exports all the gesture in an XML file.
     */
    void toogleExport();
    /*!
     * \brief refreshListViewContent slot called when the content of the GestureListView has changed. It retrains the model
     * if the parameter boolean is set to true.
     * \param pTrain defines weither or not to retrain the model
     */
    void refreshListViewContent(bool pTrain = true);
    /*!
     * \brief updateCommand slot called when the Command of the Gesture has changed in the CommandChooser. It updates the
     * DAOLayer
     */
    void updateCommand();
    /*!
     * \brief updateRecordName slot called when the Name of the Gesture has changed in the CommandChooser. It updates the
     * DAOLayer and the GestureListView
     */
    void updateRecordName();
};

#endif // LISTVIEW_H
