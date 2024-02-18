#ifndef SENSOR_REPOSITORY_JSON_REPOSITORY_H
#define SENSOR_REPOSITORY_JSON_REPOSITORY_H

#include <string>
#include <map>

#include "SRepository.h"
#include "../DataMapper/JsonFile.h"

namespace Sensor {
namespace Repository {

class JsonRepository : public SRepository {
  private:
    DataMapper::JsonFile data_mapper;
    std::map<unsigned int, AbstractSensor*> repository;

  public:
    JsonRepository(DataMapper::JsonFile data_mapper);
    
    static JsonRepository fromPath(const std::string path); // Static factory method
    const DataMapper::JsonFile& getDataMapper() const;
    const std::map<unsigned int, AbstractSensor*>& getRepository() const;
    const std::string& getPath() const;
    void setPath(std::string path);
    void create(AbstractSensor* sensor) override;
    AbstractSensor* read(const unsigned int identifier) const override;
    void update(AbstractSensor* sensor) override;
    void remove(const unsigned int identifier) override;
    std::vector<AbstractSensor*> readAll() const override;
    void overwrite(const std::vector<Sensor::AbstractSensor*> newSensors) override;
    void store();
    void load();

    ~JsonRepository() override;
};

}
}
#endif