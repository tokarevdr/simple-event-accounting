import QtQuick 2.15

QtObject {
    id: root

    enum View {
        EventsInfo,
        Event,
        Receipt,
        ReceiptItem
    }

    property int currentView: 0
}
