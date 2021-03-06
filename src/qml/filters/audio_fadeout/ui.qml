/*
 * Copyright (c) 2014-2015 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import Shotcut.Controls 1.0

Item {
    width: 100
    height: 50
    objectName: 'fadeOut'
    property alias duration: timeSpinner.value

    Component.onCompleted: {
        if (filter.isNew) {
            duration = Math.ceil(settings.audioOutDuration * profile.fps)
            filter.set('gain', 1)
            filter.set('end', 0)
            filter.set('out', filter.producerOut)
            filter.set('in', filter.getDouble('out') - duration + 1)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8

        RowLayout {
            Label { text: qsTr('Duration') }
            TimeSpinner {
                id: timeSpinner
                minimumValue: 1
                maximumValue: 5000
                value: filter.getDouble('out') - filter.getDouble('in') + 1
                onValueChanged: {
                    filter.set('in', filter.getDouble('out') - duration + 1)
                }
                onSetDefaultClicked: {
                    duration = Math.ceil(settings.audioOutDuration * profile.fps)
                }
                onSaveDefaultClicked: {
                    settings.audioOutDuration = duration / profile.fps
                }
            }
        }
        Item {
            Layout.fillHeight: true;
        }
    }
}
