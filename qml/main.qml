/***************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import diy 1.0
ApplicationWindow {
    id: wroot
    visible: true
    width: 720
    height: 720
    title: qsTr("Gameboy")
    Item {
        id: keyItem
        Keys.onPressed:{
            if(event.key === Qt.Key_Up ) {
                mainProcess.handleButtonPressed(0,true);
            } else if(event.key === Qt.Key_Down ) {
                mainProcess.handleButtonPressed(1,true);
            } else if(event.key === Qt.Key_Left ) {
                mainProcess.handleButtonPressed(2,true);
            } else if(event.key === Qt.Key_Right ) {
                mainProcess.handleButtonPressed(3,true);
            } else if(event.key === Qt.Key_Space ) {
                mainProcess.handleButtonPressed(4,true);
            } else if(event.key === Qt.Key_B ) {
                mainProcess.handleButtonPressed(5,true);
            }
        }
        Keys.onReleased:{
            if(event.key === Qt.Key_Up ) {
                mainProcess.handleButtonPressed(0,false);
            } else if(event.key === Qt.Key_Down ) {
                mainProcess.handleButtonPressed(1,false);
            } else if(event.key === Qt.Key_Left ) {
                mainProcess.handleButtonPressed(2,false);
            } else if(event.key === Qt.Key_Right ) {
                mainProcess.handleButtonPressed(3,false);
            } else if(event.key === Qt.Key_Space ) {
                mainProcess.handleButtonPressed(4,false);
            } else if(event.key === Qt.Key_B ) {
                mainProcess.handleButtonPressed(5,false);
            }
        }
    }

    MainProcess {
        id: mainProcess
        onReadyToUpdate: {
            mainProcess.updateScreen();
        }
    }
    
    Button{
        id: btnRight
        x: 214
        y: 599
        text: "Right"
        font.pointSize: 12
        onPressed: {
            mainProcess.handleButtonPressed(3,true);
        }
        onReleased: {
            mainProcess.handleButtonPressed(3,false);
        }
    }
    Button{
        id: btnLeft
        x: 10
        y: 599
        text: "Left"
        font.pointSize: 12
        onPressed: {
            mainProcess.handleButtonPressed(2,true);
        }
        onReleased: {
            mainProcess.handleButtonPressed(2,false);
        }
    }
    Button{
        id: btnDown
        x: 113
        y: 669
        text: "Down"
        font.pointSize: 12
        onPressed: {
            mainProcess.handleButtonPressed(1,true);
        }
        onReleased: {
            mainProcess.handleButtonPressed(1,false);
        }
    }
    Button{
        id: btnUp
        x: 113
        y: 531
        text: "Up"
        font.pointSize: 12
        onPressed: {
            mainProcess.handleButtonPressed(0,true);
        }
        onReleased: {
            mainProcess.handleButtonPressed(0,false);
        }
    }
    
    Button {
        id: btnBack
        x: 605
        y: 563
        width: 105
        height: 101
        text: "Back"
        font.pointSize: 12
        onPressed: {
            mainProcess.handleButtonPressed(5,true);
        }
        onReleased: {
            mainProcess.handleButtonPressed(5,false);
        }
    }
    Button {
        id: btnEnter
        x: 409
        y: 563
        width: 105
        height: 101
        text: "Enter"
        font.pointSize: 12
        onPressed: {
            mainProcess.handleButtonPressed(4,true);
        }
        onReleased: {
            mainProcess.handleButtonPressed(4,false);
        }
    }
    Rectangle {
        id: rectangle
        x: 10
        y: 12
        width: 700
        height: 500
        color: "#84af40"
        Item {
            id: canvas
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 49
            anchors.topMargin: 71
            width: 605
            height: 390
            VideoRender {
                id: videoRender
                anchors.fill: parent
            }
        }

        Label {
            id: lblMachineState
            x: 8
            y: 8
            width: 682
            height: 57
            color: "#ffffff"
            text: qsTr("MACHINE_STATE")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
            
            
        }
    }
    
    Component.onCompleted: {
        keyItem.focus = true;
        mainProcess.setRender(videoRender);
        mainProcess.startService();
    }
}

