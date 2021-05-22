// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PEERTABLEMODEL_H
#define BITCOIN_QT_PEERTABLEMODEL_H

#include <net_processing.h> // For CNodeStateStats
#include <net.h>

#include <memory>

#include <QAbstractTableModel>
#include <QStringList>

class PeerTablePriv;

namespace interfaces {
class Node;
}

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

struct CNodeCombinedStats {
    CNodeStats nodeStats;
    CNodeStateStats nodeStateStats;
    bool fNodeStateStatsAvailable;
};
Q_DECLARE_METATYPE(CNodeCombinedStats*)

/**
   Qt model providing information about connected peers, similar to the
   "getpeerinfo" RPC call. Used by the rpc console UI.
 */
class PeerTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PeerTableModel(interfaces::Node& node, QObject* parent);
    ~PeerTableModel();
    void startAutoRefresh();
    void stopAutoRefresh();

    enum ColumnIndex {
        NetNodeId = 0,
        Address,
        ConnectionType,
        Network,
        Ping,
        Sent,
        Received,
        Subversion
    };

    enum {
        StatsRole = Qt::UserRole,
    };

    /** @name Methods overridden from QAbstractTableModel
        @{*/
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*@}*/

public Q_SLOTS:
    void refresh();

private:
    interfaces::Node& m_node;
    const QStringList columns{
        /*: Title of Peers Table column which contains a
            unique number used to identify a connection. */
        tr("Peer"),
        /*: Title of Peers Table column which contains the
            IP/Onion/I2P address we used to connect to the peer. */
        tr("Address"),
        /*: Title of Peers Table column which contains a value for
            the type of connection we have established with the peer.
            Type is a term denoting what the connection is for. */
        tr("Type"),
        /*: Title of Peers Table column which contains a value for
            the network the peer resides on. */
        tr("Network"),
        /*: Title of Peers Table column which contains a value for
            the latency of the connection established with the peer. */
        tr("Ping"),
        /*: Title of Peers Table column which contains a value for
            the total amount of bytes we have sent to the peer. */
        tr("Sent"),
        /*: Title of Peers Table column which contains a value for
            the total amount of bytes we have received from the peer. */
        tr("Received"),
        /*: Title of Peers Table column which contains the peer's
            User Agent string. A peer can configure this value to
            allow itself to be identifiable. */
        tr("User Agent")};
    std::unique_ptr<PeerTablePriv> priv;
    QTimer *timer;
};

#endif // BITCOIN_QT_PEERTABLEMODEL_H
