
int main()
{
    Number x = "197 802"; //
    Number y = "263 736"; //
    Number z = "395 604"; //

    for (Number nb : {x, y, z})
    {
        sum(nb[_3]) & sum(nb[_2]) & period(9); // true

        nb <<= 2; //
        sum(nb[_3]) & sum(nb[_2]) & period(9); // true

        nb <<= 2; //
        sum(nb[_3]) & sum(nb[_2]) & period(9); // true

        sum(nb<<=2, nb<<=2, nb<<=2) & period(9); // true
    }

    (x + x/3) == y; // true
    (x + 34percent2) == y; // true

    (y + y/2) == z; // true
    (y + 51percent2) == z; // true

    (x * 2) = z; // true
}