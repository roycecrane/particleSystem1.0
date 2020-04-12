#version 300 es
layout(location =  0) in vec3 posin;
layout(location =  1) in vec3 vel;
layout(location =  2) in vec3 outp;
layout(location = 3 ) in vec3 initP;

uniform vec3 touch;
uniform vec3 seeker;
uniform vec3 button;

out vec3 P;
out vec3 V;
out vec3 O;
out vec3 IP;
out vec3 B;
void color(float e, out vec3 O){
    if(e <= 0.1f ){O= vec3(1.0,1.0,1.0);}
    if(e <= 0.2f && e > 0.1f) O= vec3(0.5,0.5,0.0);
    if(e <= 0.3f && e > 0.2f) O= vec3(0.0,0.5,0.0);
    if(e <= 0.4f && e > 0.3f) O= vec3(0.5,0.3,0.0);
    if(e <= 0.5f && e > 0.4f) O= vec3(0.0,0.3,0.5);
    if(e <= 0.6f && e > 0.5f) O= vec3(0.0,0.5,1.0);
    if(e <= 0.7f && e > 0.6f) O= vec3(0.5,0.0,0.0);
    if(e <= 0.8f && e > 0.7f) O= vec3(0.2,0.5,0.2);
    if(e <= 0.9f && e > 0.8f) O= vec3(0.5,0.5,0.0);
    if(e <= 1.0f && e > 0.9f) O= vec3(0.0,0.3,0.0);
    if(e <= 1.2f && e > 1.0f) O= vec3(0.0,0.5,0.5);
    if(e > 1.2f) O= vec3(0.0f,0.3,0.3);

}
void toCart( float r,  float theta, float rDot, float thetaDot, out vec3 pos, out vec3 vel){
    pos.y = r * sin(theta);
    pos.x = r * cos(theta);
    vel.x = rDot * cos(theta) -  r * thetaDot * sin(theta);
    vel.y = rDot * sin(theta) +  r * thetaDot * cos(theta);
}

void toPolar( vec3 POS, vec3 VEL, out float R, out float THETA, out float RDOT, out float THETADOT)
{
    float pi = 3.14159265359;
    RDOT = ((POS).x * (VEL).x + (POS).y * (VEL).y)/sqrt((POS).x * (POS).x + (POS).y * (POS).y );
    THETADOT = ((POS).x * (VEL).y - (POS).y * (VEL).x)/((POS).x * (POS).x + (POS).y * (POS).y );
    THETA = atan((POS).y,(POS).x);
    if (THETA < 0.0) THETA += 2.0 * pi;
    R = length(vec2((POS).x,(POS).y));
}

void main() {
    vec3 pos, angMom, LRL;
    vec3 newA;
    float L, e, psi, newPsi, rDD,thtDD,toOrAway,rotDirection,sizePsi;
    float r, theta,thetaDot,rDot;
    //settings
    int touchOn = 1;
    float resetVelocity =1.0f*pow(10.0f,11.0f);
    float worldScale = 1.0f*pow(10.0f,-6.0f);
    float dt = 2.0f*pow(10.0f,-15.0f);
    float k = 0.8f * pow(10.0f,4.0f);

    float pi = 3.14159265359f;

    float SEEK = (1.0-seeker.x/ 100.0f);
    k *= (SEEK*30.0f);
    P = vec3((posin).xy,0.0f);
    V = vec3((vel).xy,0.0f);
    O = outp;
    IP = initP;

    if(touchOn == 1 ) P.xy = P.xy - vec2(touch.xy);

    pos =  P * worldScale;
    V = worldScale * V;

    toPolar(pos,V,r,theta,rDot,thetaDot);

    V.x = rDot * cos(theta) -  r * thetaDot * sin(theta);
    V.y = rDot * sin(theta) +  r * thetaDot * cos(theta);

    angMom = (cross(pos,V));
    L = length(angMom);
    LRL = cross( V, angMom) - k*pos/length(pos);
    e = length(LRL)/(k);

    sizePsi =dot(LRL,pos);
    rotDirection = (cross(pos,V)).z;
    toOrAway = 1.0f * sign((cross(LRL,pos)).z);
    psi = (asin((cross( LRL/length(LRL), pos/length(pos) )).z ));

    if(isnan(psi)) psi = pi/2.0 * toOrAway;

    thtDD = -2.0*L*rDot/(r*r*r);
    rDD = thetaDot*thetaDot * r - k/(r*r);

    if(toOrAway < 0.0f && sizePsi < 0.0f)psi = -pi - psi;
    if(toOrAway > 0.0f && sizePsi < 0.0f)psi = pi - psi;
    r = r + (rDot) * dt + 0.5*rDD*dt*dt;

    if(rotDirection < 0.0){
        thtDD *= -1.0f;
        newPsi = psi + thetaDot * dt + 0.5 * thtDD * dt * dt;
        newPsi*=-1.0f;
    }
    if(rotDirection > 0.0) newPsi = psi + thetaDot * dt + 0.5 * thtDD * dt * dt;

    theta = theta + thetaDot * dt + 0.5 * thtDD * dt*dt;
    rDot = k / L * e * sin(newPsi);
    thetaDot = L/(r*r)*sign(thetaDot);

    if( dot(LRL,pos) < 0.0 && (cross(pos,LRL)).z == 0.0) psi = pi;
    if( dot(LRL,pos) > 0.0 && (cross(pos,LRL)).z == 0.0) psi = 0.0;

    toCart(r,theta, rDot,thetaDot, pos, V);
    newA =cross( V, cross(pos,V)) - k * pos/length(pos);

    V = V/worldScale;
    P = pos/worldScale;
    if(touchOn == 1 )P.xy=P.xy+touch.xy;
//    if(length(e) >= 0.5 ){
//        V=vec3(0.0f,resetVelocity,0.0);
//        P=initP;
//    }
//    P=initP;
    B = vec3(0);
    O = vec3(0);
    O.z = e*e;
    O.y = 0.5*(length(cross(LRL/length(LRL),P/length(P))));
    O.x = 0.4f*length(length(LRL)-length(newA));
    float rM = 90000.0f*L*L/(k*(1.0f-e));
     color(e,O);
}
//layout(location = 0) in vec3 posin;
////layout(location = 1) in vec3 initP;
//uniform vec3 seeker;
//out vec3 P;
//void main() {
//    P= posin;
//    P.z=1.0f;
//    P.x+= 0.01f*P.y*seeker.x/50.0f;
//    P.y-= 0.01f*P.x;
//
//    //    P.x =0.5*seeker.x/20.0;
//
//}
//\0
