#include <priv/SizeIndexEntries.h>
using namespace FM;

#include <QMutexLocker>

class FakeEntry : public Entry
{
public:
   FakeEntry(qint64 size) : Entry(nullptr, QString(), size) {}
   ~FakeEntry() {}

   QString getFullPath() const { return QString(); }
   QString getPath() const { return QString(); }
   SharedDirectory* getRoot() const { return nullptr; }
   void removeUnfinishedFiles() {}
   void moveInto(Directory* directory) {}
};

/////

SizeIndexEntries::SizeIndexEntries()
{
   this->index.setSortedFunction([](Entry* e1, Entry* e2) {
      if (e1->getSize() == e2->getSize())
      {
         const QString& name1 = e1->getName().toLower();
         const QString& name2 = e2->getName().toLower();

         if (name1 == name2 )
            return qHash(e1) < qHash(e2);

         return name1 < name2;
      }

      return e1->getSize() < e2->getSize();
   });
}

void SizeIndexEntries::addItem(Entry* item)
{
   QMutexLocker locker(&this->mutex);
   this->index.insert(item);
}

void SizeIndexEntries::rmItem(Entry* item)
{
   QMutexLocker locker(&this->mutex);
   this->index.remove(item);
}

QList<Entry*> SizeIndexEntries::search(qint64 sizeMin, qint64 sizeMax, std::function<bool(const Entry*)> predicat) const
{
   QMutexLocker locker(&this->mutex);
   QList<Entry*> result;

   if (this->index.isEmpty())
      return result;

   FakeEntry searchEntry(sizeMin);
   auto i = this->index.iteratorOfNearest(&searchEntry);

   if ((*i)->getSize() < sizeMin)
      ++i;

   auto end = this->index.end();

   while (i != end && (*i)->getSize() <= sizeMax)
      if (predicat == nullptr || predicat(*i))
         result << *i;

   return result;
}
