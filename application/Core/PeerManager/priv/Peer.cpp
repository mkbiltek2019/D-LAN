#include <priv/Peer.h>

using namespace PeerManager;

/**
 * Constructor: Create a new peer, based on his ID
 * @author mcuony
 */

::Peer::Peer(Common::Hash ID_) {
    ID = ID_;
}

/**
 * Set the lastUpdate to now
 *
 * @author mcuony
 */
void ::Peer::justSeen() {
    IisAlive = true;
    lastUpdate =  QDateTime::currentDateTime();
}

/**
 * Test if the peer is dead or not, and set IisAlive
 *
 * @author mcuony
 */
bool ::Peer::haveYouToDie() {
    int nSec = lastUpdate.secsTo(QDateTime::currentDateTime()) ;

    if (nSec > TTL) {
        IisAlive = false;
        return true;
    }
    return false;
}

/**
 * Return true if the peer is alive
 *
 * @author mcuony
 */
bool ::Peer::isAlive() {
    return IisAlive;
}

/**
 * Return the id of the peer
 *
 * @author mcuony
 */
Common::Hash* ::Peer::getId() {
    return &ID;
}

/*TODO*/
void ::Peer::send(const QByteArray& data) {
}
Common::Hashes* ::Peer::getHashes(const Protos::Common::FileEntry& file) {
}
IGetEntries* ::Peer::getEntries(const Protos::Common::DirEntry& dir) {
}
void ::Peer::receive(QByteArray& data) {
}
