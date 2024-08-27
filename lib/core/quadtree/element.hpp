
#ifndef _QUADTREE_ELEMENT_HPP

  #define _QUADTREE_ELEMENT_HPP

  template <class class_type>
  class QuadtreeElement {

    public:
      class_type value;

      float horzPos;
      float vertPos;
      //float width;
      //float height;

      QuadtreeElement(float horzPos, float vertPos) {
        this->horzPos = horzPos;
        this->vertPos = vertPos;
      }

  };

#endif
