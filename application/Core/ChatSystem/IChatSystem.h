/**
  * D-LAN - A decentralized LAN file sharing software.
  * Copyright (C) 2010-2012 Greg Burri <greg.burri@gmail.com>
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
  
#ifndef ICHATSYSTEM_ICHAT_H
#define ICHATSYSTEM_ICHAT_H

#include <limits>

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include <Core/PeerManager/IPeer.h>

#include <Protos/common.pb.h>

namespace CS
{
   class IChatSystem : public QObject
   {
      Q_OBJECT
   public:
      virtual ~IChatSystem() {}

      /**
        * Send a message to everyone.
        * This will emit a 'newMessages' signal.
        */
      virtual void send(const QString& message) = 0;

      virtual void send(const QString& message, const QString& roomName) = 0;

      /**
        * Retrieve the last 'number' known message.
        */
      virtual void getLastChatMessages(Protos::Common::ChatMessages& chatMessages, int number = std::numeric_limits<int>::max(), const QString& room = QString()) const = 0;

      struct ChatRoom
      {
         QString name;
         QSet<PM::IPeer*> peers;
         bool joined;
      };

      virtual QList<ChatRoom> getRooms() const = 0;

      virtual void joinRoom(const QString& room) = 0;

      virtual void leaveRoom(const QString& room) = 0;

   signals:
      /**
        * Emitted when one or more messages are received.
        * The message can come from the main chat or from a joined room.
        */
      void newMessages(const Protos::Common::ChatMessages&);
   };
}
#endif
