#ifndef WAYPOINT_HPP_
#define WAYPOINT_HPP_

class Waypoint {
    public:
        Waypoint(const int x, const int y);
        ~Waypoint() = default;

        void setX(const int x);
        void setY(const int y);

        int getX(void) const;
        int getY(void) const;

    protected:
    private:
        int _x;
        int _y;
};

#endif /* !WAYPOINT_HPP_ */
