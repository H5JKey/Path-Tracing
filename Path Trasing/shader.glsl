struct Box 
{
    vec3 position;
    vec3 size;
    vec3 color;
    float diffuseness;
    bool lightEmitter;
    float opacity;
};

struct Sphere 
{
    vec3 position;
    float size;
    vec3 color;
    float diffuseness;
    bool lightEmitter;
    float opacity;
};



uniform float time;
uniform vec2 resolution;
uniform Box[20] boxes;
uniform Sphere[20] spheres;
uniform vec3 position;
uniform vec3 rotation;
uniform bool normalsOn;
uniform int Nbox;
uniform int Nsphere;
uniform sampler2D u_sample;
uniform float u_sample_part;
uniform int reflections;
uniform int samples;

struct HitInfo 
{
    float distance;
    float farDistance;
    vec3 point;
    vec3 farPoint;
    vec3 color;
    vec3 normal;
    float diffuseness;
    bool lightEmitter;
    float opacity;
};




HitInfo boxIntersection(vec3 ro, vec3 rd, Box box) {
    HitInfo hitInfo;
    vec3 m=1.0/rd;
    vec3 n = m*(ro-box.position-box.size/2);
    vec3 k=abs(m)*box.size/2;
    vec3 t1= - n - k;
    vec3 t2= - n + k;
    float tN=max(max(t1.x,t1.y),t1.z);
    float tF=min(min(t2.x,t2.y),t2.z);
    if (tN>tF || tF<=0.0) {

        hitInfo.distance=-1.0;
        hitInfo.farDistance=-1.0;
        hitInfo.color=vec3(0.0);
    }
    else {
        hitInfo.normal = (tN>0.0) ? step(vec3(tN),t1) : // ro ouside the box
                           step(t2,vec3(tF));  // ro inside the box
        hitInfo.normal *= -sign(rd);
        hitInfo.distance=tN;
        hitInfo.farDistance=tF;
        hitInfo.color=box.color;
        hitInfo.point=hitInfo.distance*rd+ro;
        hitInfo.farPoint=hitInfo.farDistance*rd+ro;
        hitInfo.diffuseness=box.diffuseness;
        hitInfo.lightEmitter=box.lightEmitter;
        hitInfo.opacity=box.opacity;
    }
    return hitInfo;
}


HitInfo sphereIntersection(vec3 ro, vec3 rd, Sphere sphere)
{
    HitInfo hitInfo;
    vec3 oc = ro - sphere.position;
    float b = dot( oc, rd );
    float c = dot( oc, oc ) - sphere.size*sphere.size;
    float h = b*b - c;
    if( h<0.0) {
        hitInfo.distance=-1.0;
        hitInfo.farDistance=-1.0;
        hitInfo.color=vec3(0.0);
    }
    else {
        h = sqrt( h );
        
        hitInfo.distance=-b-h;
        hitInfo.farDistance=-b+h;
        hitInfo.color=sphere.color;
        hitInfo.point=hitInfo.distance*rd+ro;
        hitInfo.farPoint=hitInfo.farDistance*rd+ro;
        hitInfo.diffuseness=sphere.diffuseness;
        hitInfo.lightEmitter=sphere.lightEmitter;
        hitInfo.opacity=sphere.opacity;
        hitInfo.normal=normalize(hitInfo.point-sphere.position);
    }
    return hitInfo;
}




#define MAX_DISTANCE 10000
HitInfo rayCasting(vec3 ro, vec3 rd) {
    HitInfo hitInfo;
    hitInfo.color=vec3(0,0.0,0);
    hitInfo.distance=MAX_DISTANCE;
    for (int i=0; i<Nbox; i++) {
        HitInfo hit = boxIntersection(ro,rd,boxes[i]);
        if (hit.distance<0) {
            continue;
        }
        if (hit.distance<hitInfo.distance) {
            hitInfo=hit;
        }
    }
    for (int i=0; i<Nsphere; i++) {
        HitInfo hit = sphereIntersection(ro,rd,spheres[i]);
        if (hit.distance<0) {
            continue;
        }
        if (hit.distance<hitInfo.distance) {
            hitInfo=hit;
        }
    }
   return hitInfo;
    
}


float random(float co) { return fract(sin(co*(91.3458)) * 47453.5453); }
float random(vec2 co){ return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453); }
float random(vec3 co){ return random(co.xy+random(co.z)); }
vec3 randomOnSphere(vec3 co){
  vec3 rand= vec3(random(co*(time)*2.0),random(co*(time)*4.0),random(co*(time)));
  
  float theta = rand.x * 2.0 * 3.14159265;
  float v = rand.y;
  float phi = acos (2.0 * v-1.0);
  float r = pow(rand.z,1.0 / 3.0);
  float x=r*sin(phi)*cos (theta);
  float y=r* sin(phi)*sin(theta);
  float z=r*cos(phi);
  return vec3(x, y, z);
}



vec3 render(vec3 ro,vec3 rd) {
   vec3 color=vec3(1);
   float f=1.0;
   for (int i=0; i<reflections; i++) {
      HitInfo hitInfo=rayCasting(ro,rd);

      if (hitInfo.distance<0 || hitInfo.distance==MAX_DISTANCE)
        return color*f*hitInfo.color;
      if (hitInfo.lightEmitter) 
        return color*hitInfo.color*f;
      
      color*=f*hitInfo.color;
      if (hitInfo.opacity>0) {
        vec3 refracted=refract(rd,hitInfo.normal,hitInfo.opacity);
        if (refracted==vec3(0.0))
            rd=reflect(rd,hitInfo.normal);
        else
            rd=refracted;
        ro=hitInfo.farPoint;
      }
      else {
        vec3 ideal=reflect(rd,hitInfo.normal);
        vec3 rnd=randomOnSphere(hitInfo.point);
        rnd=normalize(rnd*dot(rnd,hitInfo.normal));
        rd=mix(ideal,rnd,hitInfo.diffuseness);
        ro=hitInfo.point;
      }
      f*=0.8;   
      
   }
   return vec3(0);
}

mat2 rotate(float angle) {
    float radAngle = radians(angle);
    
    float sin = sin(radAngle);
    float cos = cos(radAngle);
    
    return mat2(cos, -sin, sin, cos);
}

void main() {
    vec2 uv = (2.0*gl_FragCoord.xy-resolution.xy)/resolution.y;
    vec3 rd = normalize(vec3(uv, 1.0));
    rd.yz*=rotate(-rotation.x);
    rd.xz*=rotate(-rotation.y);
    rd.zy*=rotate(-rotation.z);

    vec3 col = vec3(0.0);
    for(int i = 0; i < samples; i++) {
		col += render(position,rd);
	}
	col /= samples;
	float white = 20.0;
	col *= white * 16.0;
	col = (col * (1.0 + col / white / white)) / (1.0 + col);
	vec3 sampleCol = texture(u_sample, gl_TexCoord[0].xy).rgb;
	col = mix(sampleCol, col, u_sample_part);
	gl_FragColor = vec4(col, 1.0);
}





