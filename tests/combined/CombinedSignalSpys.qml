import QtQuick 2.4
import QtTest 1.2

QtObject {
    property var dest
    property var otherDest

    readonly property var event1Spy: SignalSpy {
        target: dest
        signalName: "event1"
    }

    readonly property var eventCombiEnumSpy: SignalSpy {
        target: dest
        signalName: "eventCombiEnum"
    }

    readonly property var eventIntSpy: SignalSpy {
        target: dest
        signalName: "eventInt"
    }

    readonly property var eventBoolAndCombiStructSpy: SignalSpy {
        target: dest
        signalName: "eventBoolAndCombiStruct"
    }

    readonly property var eventWithListSpy: SignalSpy {
        target: dest
        signalName: "eventWithList"
    }

    readonly property var eventWithMapSpy: SignalSpy {
        target: dest
        signalName: "eventWithMap"
    }

    readonly property var eventWithStructWithListSpy: SignalSpy {
        target: dest
        signalName: "eventWithStructWithList"
    }

    readonly property var intPropertyChangedSpy: SignalSpy {
        target: dest
        signalName: "intPropertyChanged"
    }

    readonly property var stringListPropertyChangedSpy: SignalSpy {
        target: dest
        signalName: "stringListPropertyChanged"
    }

    readonly property var otherEventSpy: SignalSpy {
        target: otherDest
        signalName: "otherEvent"
    }
}
