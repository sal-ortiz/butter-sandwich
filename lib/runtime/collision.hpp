
#ifndef _COLLISION_HPP

  #define _COLLISION_HPP


  class Collision {

    public:

      static bool evaluate(Position* basePos, Size* baseSize, Position* testPos, Size* testSize) {

        if (
          (
            (
              (basePos->horz > testPos->horz) && (basePos->horz < testPos->horz + testSize->horz) &&
              (basePos->vert > testPos->vert) && (basePos->vert < testPos->vert + testSize->vert)
            ) || (
              (basePos->horz + baseSize->horz > testPos->horz) && (basePos->horz + baseSize->horz < testPos->horz + testSize->horz) &&
              (basePos->vert + baseSize->vert > testPos->vert) && (basePos->vert + baseSize->vert < testPos->vert + testSize->vert)
            )
          ) || (
            (
              (testPos->horz > basePos->horz) && (testPos->horz < basePos->horz + baseSize->horz) &&
              (testPos->vert > basePos->vert) && (testPos->vert < basePos->vert + baseSize->vert)
            ) || (
              (testPos->horz + testSize->horz > basePos->horz) && (testPos->horz + testSize->horz < basePos->horz + baseSize->horz) &&
              (testPos->vert + testSize->vert > basePos->vert) && (testPos->vert + testSize->vert < basePos->vert + baseSize->vert)
            )
          )
        ) {
          return true;
        }

        return false;
      }

  };

#endif
