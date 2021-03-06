#ifndef EXECUTION_HH
#define EXECUTION_HH

#include <QObject>
#include "data.hh"
#include <sstream>

class Execution : public QObject {
    Q_OBJECT
public:
    Execution() {
        NodeAllocator* na = new NodeAllocator(false);
        _data = new Data(na, true);

        
    }

    inline const std::unordered_map<unsigned long long, string>& getNogoods(void) { return _data->getNogoods(); }
    inline std::unordered_map<unsigned long long, string>& getInfo(void) { return _data->getInfo(); }
    DbEntry* getEntry(unsigned int gid) { return _data->getEntry(gid); }
    unsigned int getGidBySid(unsigned int sid) { return _data->getGidBySid(sid); }
    const char* getLabel(unsigned int gid) { return _data->getLabel(gid); }
    unsigned long long getTotalTime() { return _data->getTotalTime(); }
    string getTitle() { return _data->getTitle(); }

    string getDescription() {
        std::stringstream ss;
        ss << "an execution with " << _data->size() << " nodes";
        return ss.str();
    }


    Data* getData() {
        return _data;
    }



    
signals:
    void newNode();
    void startReceiving();
    void doneReceiving();
private:
    Data* _data;
public Q_SLOTS:
    void handleNewNode(message::Node& node) {
        std::cerr << "execution::newNode\n";
        _data->handleNodeCallback(node);
        //
        emit newNode();
    }
};

#endif
