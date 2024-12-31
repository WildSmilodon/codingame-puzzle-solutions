#ifndef TILETYPE_H
#define TILETYPE_H

#include <string>

class TileType {
public:
    // Constructor
    TileType(int x, int y, const std::string& type = "EMPTY", int owner = -1,
             int organ_id = 0, const std::string& organ_dir = "X",
             int organ_parent_id = 0, int organ_root_id = 0);

    // Getters and setters
    int getX() const;
    int getY() const;
    const std::string& getType() const;
    int getOwner() const;
    int getOrganId() const;
    const std::string& getOrganDir() const;
    int getOrganParentId() const;
    int getOrganRootId() const;
    bool isVitamin() const;

    void setType(const std::string& type);
    void setOwner(int owner);
    void setOrganId(int organ_id);
    void setOrganDir(const std::string& organ_dir);
    void setOrganParentId(int parent_id);
    void setOrganRootId(int root_id);

private:
    int x, y;                  // Grid coordinates
    std::string type;          // Type of the tile
    int owner;                 // Owner: 1 (you), 0 (enemy), -1 (neither)
    int organ_id;              // Organ ID (0 if not an organ)
    std::string organ_dir;     // Direction (N, E, S, W, or X)
    int organ_parent_id;       // Parent organ ID
    int organ_root_id;         // Root organ ID
};

#endif // TILETYPE_H