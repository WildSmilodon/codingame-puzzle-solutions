#include "TileType.h"

// Constructor
TileType::TileType(int x, int y, const std::string& type, int owner,
                   int organ_id, const std::string& organ_dir,
                   int organ_parent_id, int organ_root_id)
    : x(x), y(y), type(type), owner(owner), organ_id(organ_id),
      organ_dir(organ_dir), organ_parent_id(organ_parent_id), organ_root_id(organ_root_id) {}

// Getters
int TileType::getX() const { return x; }
int TileType::getY() const { return y; }
const std::string& TileType::getType() const { return type; }
int TileType::getOwner() const { return owner; }
int TileType::getOrganId() const { return organ_id; }
const std::string& TileType::getOrganDir() const { return organ_dir; }
int TileType::getOrganParentId() const { return organ_parent_id; }
int TileType::getOrganRootId() const { return organ_root_id; }
bool TileType::isVitamin() const { return type == "A" || type == "B" || type == "C" || type == "D"; }

// Setters
void TileType::setType(const std::string& type) { this->type = type; }
void TileType::setOwner(int owner) { this->owner = owner; }
void TileType::setOrganId(int organ_id) { this->organ_id = organ_id; }
void TileType::setOrganDir(const std::string& organ_dir) { this->organ_dir = organ_dir; }
void TileType::setOrganParentId(int parent_id) { this->organ_parent_id = parent_id; }
void TileType::setOrganRootId(int root_id) { this->organ_root_id = root_id; }