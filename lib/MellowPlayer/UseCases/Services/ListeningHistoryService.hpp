#pragma once

#include <QMap>
#include <QMutex>
#include <QList>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>
#include <MellowPlayer/UseCases/IWorkDispatcher.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IListeningHistoryDataProvider;
class ILogger;
class IPlayer;

class ListeningHistoryService: public QObject {
    Q_OBJECT
public:
    ListeningHistoryService(IListeningHistoryDataProvider& model, IPlayer& player, IWorkDispatcher& workDispatcher);

    void initialize();
    const QList<Entities::ListeningHistoryEntry>& getEntries() const;
    void clear();
    void removeById(int entryId);
    void removeByService(const QString& serviceName);

signals:
    void entryAdded(const Entities::ListeningHistoryEntry& entry);
    void entryRemoved(int i);
    void entriesCleared();

private slots:
    void onPlaybackStatusChanged();
    void onCurrentSongChanged(Entities::Song* song);

private:
    ILogger& logger;
    IListeningHistoryDataProvider& dataProvider;
    IPlayer& player;
    IWorkDispatcher& workDispatcher;
    QMap<QString, Entities::ListeningHistoryEntry> previousEntryPerPlayer;
    QList<Entities::ListeningHistoryEntry> entries;
};

END_MELLOWPLAYER_NAMESPACE