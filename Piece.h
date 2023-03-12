#ifndef PROJECT1_PIECE_H
#define PROJECT1_PIECE_H


class Piece {
private:
    int id;
    char sym;
    int level;
    int pos;
public:

    Piece(int i, char s);
    Piece();

    void setId(int i);
    void setSym(char s);
    void setCoords(int l, int p);
    int getId() const;
    char getSym() const;
    int getPos() const;
    int getLevel() const;
};


#endif //PROJECT1_PIECE_H
