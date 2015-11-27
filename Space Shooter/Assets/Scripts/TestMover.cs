using UnityEngine;
using System.Collections;

public class TestMover : MonoBehaviour
{
    public float speed;
    public float turnSpeed;
    private GameObject target = null;
    private Vector3 dir;
    private Quaternion rot;
    // Use this for initialization
    void Start()
    {
        float minPos = float.PositiveInfinity;
        Mover[] asteroids = GameObject.FindObjectsOfType<Mover>();

        foreach (Mover aster in asteroids)
        {
            float distance = Mathf.Abs(this.transform.position.x - aster.transform.position.x);
            if (distance < minPos)
            {
                minPos = distance;
                target = aster.gameObject;
            }
        }
    }
   
    void Update()
    {
	Vector3 move;
	dir = target.transform.position - transform.position;
	rot = Quaternion.LookRotation(dir);
	transform.rotation = Quaternion.Slerp(transform.rotation, rot, turnSpeed * Time.deltaTime);
	move = new Vector3(0, 0, speed * Time.deltaTime);
	transform.Translate(move);
    }
}
