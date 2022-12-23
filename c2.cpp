
int main()
{
    Number x = "197 802";
    Number y = "263 736";
    Number z = "395 604";

    for (Number nb : {x, y, z}) {
        sum(nb[_3]) & sum(nb[_2]) & period(9);

        nb <<= 2;
        sum(nb[_3]) & sum(nb[_2]) & period(9);

        nb <<= 2;
        sum(nb[_3]) & sum(nb[_2]) & period(9);

        sum(nb <<= 2, nb <<=2, nb <<= 2) & period(9);
    }

    

    // x +/ 3 == y;
    (x + x/3) == y;
    (x + 34percent2) == y;

    // y +/ 2 == z:
    (y + y/2) == z;
    (y + 51percent2) == z;

    (x * 2) = z;
}
