#include "JsonRepository.h"

namespace Sensor {
namespace Repository {

JsonRepository::JsonRepository(DataMapper::JsonFile data_mapper)
    : data_mapper(data_mapper)
{
    load();
}

JsonRepository JsonRepository::fromPath(std::string path) {    // Static factory method
    DataMapper::JsonFile data_mapper = DataMapper::JsonFile::fromPath(path);
    JsonRepository repository(data_mapper);
    return repository;
}

const DataMapper::JsonFile& JsonRepository::getDataMapper() const {
    return data_mapper;
}

const std::map<unsigned int, AbstractSensor*>& JsonRepository::getRepository() const {
    return repository;
}

const std::string& JsonRepository::getPath() const {
    return data_mapper.getPath();
}

void JsonRepository::setPath(std::string path) {
    data_mapper.setPath(path);
}

void JsonRepository::create(AbstractSensor* sensor) {
    repository[sensor->getIdentifier()] = sensor;
}

AbstractSensor* JsonRepository::read(const unsigned int identifier) const {
    auto it = repository.find(identifier);
    if (it == repository.end()) {
        throw std::out_of_range("Trying to read an undefined id.");
    }
    return it->second;
}

void JsonRepository::update(AbstractSensor* sensor) {
    create(sensor);
}

void JsonRepository::remove(const unsigned int identifier) {
    auto it = repository.find(identifier);
    if (it != repository.end()) {
        delete it->second;
        repository.erase(it);
    }
}

std::vector<AbstractSensor*> JsonRepository::readAll() const {
    std::vector<AbstractSensor*> sensors;
    for (const auto& entry : repository) {
        sensors.push_back(entry.second);
    }
    return sensors;
}

void JsonRepository::overwrite(const std::vector<Sensor::AbstractSensor*> newSensors) {
    // Prima di sovrascrivere, liberiamo la memoria degli oggetti nella mappa corrente
    for (const auto& pair : repository) {
        delete pair.second;
    }
    repository.clear();

    // Itera attraverso il vettore di sensori della MainWindow e inserisce i loro cloni nella mappa
    for (AbstractSensor* sensor : newSensors) {
        AbstractSensor* clonedSensor = sensor->clone();
        repository[clonedSensor->getIdentifier()] = clonedSensor;
    }
}

void JsonRepository::store() {
    data_mapper.store(readAll());
}

void JsonRepository::load() {
    std::vector<AbstractSensor*> new_sensors(data_mapper.load());

    for(AbstractSensor* sensor : new_sensors){
        repository[sensor->getIdentifier()] = sensor;
    }
}

JsonRepository::~JsonRepository() {
    for (const auto& pair : repository) {
        delete pair.second;
    }
    repository.clear();
}

}
}
