#include "character.h"

Character::Character(const std::string &fileName)
//Character::Character(const tmx::MapObject &object, const std::string &fileName)
    : Sprite(fileName)
    , m_collidingEnabled(true)
{
    load(fileName);

    //if (world) {
        //m_body = tmx::BodyCreator::Add(object, *world, b2BodyType::b2_dynamicBody);

        //b2Fixture *fixture = m_body->GetFixtureList();
        //fixture->SetDensity(1.f);
        //fixture->SetFriction(0.8f);

        //sf::Vector2f pos = tmx::BoxToSfVec(m_body->GetPosition());
    //}

    //this->setPosition(object.GetPosition());
}

Character::~Character()
{
}

void Character::setColliding(bool colliding)
{
    m_collidingEnabled = colliding;
}

bool Character::colliding()
{
    return m_collidingEnabled;
}

void Character::update(sf::Time delta)
{
    Sprite::update(delta);
}

bool Character::collideWith(Sprite *sprite)
{
    if (!m_collidingEnabled)
        return false;

    return Sprite::collideWith(sprite);
}
