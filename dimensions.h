#ifndef DIMENSIONS_H
#define DIMENSIONS_H

struct Dimensions {
    float height_;
    float width_;
    float length_;
    
    Dimensions(float h, float w, float l) 
        : height_(h), width_(w), length_(l) {}
        
    bool fitsInto(const Dimensions& other) const {
        return height_ < other.height_ && 
               width_ < other.width_ && 
               length_ < other.length_;
    }
};

#endif // DIMENSIONS_H
