
#ifndef EVENT_H_
#define EVENT_H_

#include <memory>
#include "../../ConfigReader/GeneratorFileStruct.h"

class BaseScheduler;

class Event {
private:
    std::shared_ptr<GFStructs::GeneratorFile> genfile;
public:
    virtual void apply_rules(std::shared_ptr<BaseScheduler> scheduler) = 0;
    void set_genfile(std::shared_ptr<GFStructs::GeneratorFile> genfile) {this->genfile = genfile;}
    std::shared_ptr<GFStructs::GeneratorFile> get_genfile() {return this->genfile;}
};

#endif