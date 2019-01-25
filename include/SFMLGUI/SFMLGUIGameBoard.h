//
// Created by julien vial-detambel on 02/01/2017.
//

#pragma once

#include "SFMLGUIComposition.h"
#include "SFMLGUIClickableSprite.h"

class SFMLGUIGameBoard : public SFMLGUIComposition {
public:
    class Move {
    public:
        unsigned int x;
        unsigned int y;
    };
    SFMLGUIGameBoard();
    ~SFMLGUIGameBoard();
    void handleEvent(sf::Event &event);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void placeStone(SFMLGUIClickableSprite sprite);
    void update(std::string string);
    const Move &getMove() const;
    void setSubmited(bool submited);
    const bool &getSubmited() const;
private:
    Move move_;
    sf::Texture whiteStone_;
    sf::Texture blackStone_;
    sf::Texture empty_;
    bool submited_;
};