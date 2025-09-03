void ResolveCollision(objectCircle& A, objectCircle& B, float restitution = 0.9f) {
    Vector2 delta = Vector2Subtract(B.currentPosition, A.currentPosition);
    float dist = Vector2Length(delta);
    float minDist = A.radius + B.radius;

    if (dist < minDist && dist > 0.0f) {
        // Normalize the vector
        Vector2 normal = Vector2Scale(delta, 1.0f / dist);

        // Minimum translation distance to separate balls
        float penetration = minDist - dist;
        Vector2 correction = Vector2Scale(normal, penetration / 2.0f);

        // Separate the two objects
        A.currentPosition = Vector2Subtract(A.currentPosition, correction);
        B.currentPosition = Vector2Add(B.currentPosition, correction);

        // Calculate velocities
        Vector2 vA = Vector2Subtract(A.currentPosition, A.oldPosition);
        Vector2 vB = Vector2Subtract(B.currentPosition, B.oldPosition);

        // Relative velocity
        Vector2 relVel = Vector2Subtract(vB, vA);

        // Velocity along the normal
        float velAlongNormal = Vector2DotProduct(relVel, normal);

        if (velAlongNormal > 0) return; // They are moving apart

        // Calculate impulse scalar
        float impulse = -(1.0f + restitution) * velAlongNormal / 2.0f;

        Vector2 impulseVec = Vector2Scale(normal, impulse);

        // Apply impulse to old positions to simulate bounce
        A.oldPosition = Vector2Subtract(A.oldPosition, impulseVec);
        B.oldPosition = Vector2Add(B.oldPosition, impulseVec);
    }
}
