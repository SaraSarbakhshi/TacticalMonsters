#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QDialog>
#include <QString>
#include <QPixmap>

class Characters {
public:
    QString name;
    QPixmap picture;
    int health;
    int damage;
    int mobility;
    int range;
    int type;
    int row;
    int column;

    Characters(QString n, QPixmap pic, int hp, int dp, int m, int ra, int t, int r = 100, int c = 100)
        : name(n), picture(pic), health(hp), damage(dp), mobility(m), range(ra), type(t), row(r), column(c) {}

    Characters()
        : name(""), picture(QPixmap()), health(0), damage(0), mobility(0),
        range(0), type(0), row(100), column(100) {}

    // Setters
    void setName(QString n) { name = n; }
    void setPic(QPixmap pic) { picture = pic; }
    void setHealth(int hp) { health = hp; }
    void setDamage(int dp) { damage = dp; }
    void setMobility(int m) { mobility = m; }
    void setRange(int ra) { range = ra; }

    // Getters
    QString getName() const { return name; }
    QPixmap getPic() const { return picture; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    int getRange() const { return range; }
    int getMobility() const { return mobility; }

    // Combat logic
    virtual void attack(Characters& defender) {
        this->health -= defender.damage / 2;
        defender.health -= this->damage;
    }

    // Terrain capability interface
    virtual bool canWalkOnWater() const = 0;
    virtual bool canWalkOnRock() const = 0;
    virtual bool canStandOnWater() const = 0;
    virtual bool canStandOnRock() const = 0;

    virtual ~Characters() = default;
};

// Derived Classes

class Grounded : public Characters {
public:
    Grounded(QString n, QPixmap pic, int hp, int dp, int m, int ra)
        : Characters(n, pic, hp, dp, m, ra, 1) {}

    bool canWalkOnWater() const override { return false; }
    bool canWalkOnRock() const override { return false; }
    bool canStandOnWater() const override { return false; }
    bool canStandOnRock() const override { return false; }
};

class WaterWalking : public Characters {
public:
    WaterWalking(QString n, QPixmap pic, int hp, int dp, int m, int ra)
        : Characters(n, pic, hp, dp, m, ra, 2) {}

    bool canWalkOnWater() const override { return true; }
    bool canWalkOnRock() const override { return false; }
    bool canStandOnWater() const override { return true; }
    bool canStandOnRock() const override { return false; }
};

class Floating : public Characters {
public:
    Floating(QString n, QPixmap pic, int hp, int dp, int m, int ra)
        : Characters(n, pic, hp, dp, m, ra, 3) {}

    bool canWalkOnWater() const override { return true; }
    bool canWalkOnRock() const override { return true; }
    bool canStandOnWater() const override { return true; }
    bool canStandOnRock() const override { return true; }
};

class Flying : public Characters {
public:
    Flying(QString n, QPixmap pic, int hp, int dp, int m, int ra)
        : Characters(n, pic, hp, dp, m, ra, 4) {}

    bool canWalkOnWater() const override { return true; }
    bool canWalkOnRock() const override { return true; }
    bool canStandOnWater() const override { return false; }
    bool canStandOnRock() const override { return false; }
};

#endif // CHARACTERS_H
