```bash
docker
kind
kubeadm
kubelet ...
kubectl version
minikube version
**```**

## Create Cluster
```bash
# node 생성
minikube start
minikube dashboard
kubectl get nodes
```

## Deploy an app
```bash
# kubernetes-bootcamp라는 이름으로 image를 배포
kubectl create deployment kubernetes-bootcamp --image=gcr.io/google-samples/kubernetes-bootcamp:v1
kubectl get deployments # depoly list 확인
kubectl proxy # start proxy
curl http://localhost:8001/version # proxy로부터 버전 정보 획득
```

## Explore your app
- pod는 kubernetes platform 상의 최소 단위
  - volumn(storage)
  - Cluster IP(networking) : pod 별로 IP를 한개씩 배정 받음
  - container(works, jobs)
- pod는 언제나 node 상에서 동작한다.- 
- node는 kubernetes에서 워커 머신을 말하며, 클러스터에 따라 가상 혹은 물리 머신이다.
  - 각 node는 master에 의해서 관리된다.
  - kubernetes master는 클러스터 내 노드를 통해서 pod에 대한 스케쥴링을 자동으로 처리
  - kubelet : kube master와 node간의 통신을 책임지는 프로세스. 하나의 머신상에 동작하는 파드와 컨테이너 관리

```bash
kubectl get pods # pods 리스트 간단 정보
kubectl describe pods # pods 상세 정보
export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}') # pod name을 변수로 사용하기
curl http://localhost:8001/api/v1/namespaces/default/pods/$POD_NAME/proxy/
kubectl logs $POD_NAME # POD 로그 정보 보기
kubectl exec $POD_NAME env # POD에 sh문 실행하기
```

## Expose Your App Publicly
- 쿠버네티스에서 서비스는 하나의 논리적인 파드 셋과 그 파드들에 접근할 수 있는 정책을 정의하는 추상적 개념이다. 서비스는 종속적인 파드들 사이를 느슨하게 결합되도록 해준다. 서비스는 모든 쿠버네티스 오브젝트들과 같이 YAML (보다 선호하는) 또는 JSON을 이용하여 정의된다. 

- 4가지 type의 service 형태
  - type: ClusterIP - node 내부에만 공개되어있는 IP
  - type: NodePort - node 외부에 {Node IP}:{Node Port} 형태로 공개
  - type: LoadBalance - 지원이된다면 로드밸런싱 지원하는 NodePort로 공개
  - type: ExternalName - CNAME으로 레코드 반환하여 외부 이름으로 서비스 노출

```bash
kubectl get pods
kubectl get services
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080
kubectl get services # 추가된 서비스 확인
export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
echo NODE_PORT=$NODE_PORT # Expose된 node의 포트 확인
curl $(minikube ip):$NODE_PORT # minikube node의 expose된 port에서 app=kubernetes-bootcamp를 확인해보세요.

kubectl describe deployment # deployment 라벨을 볼 수 있음. ?
kubectl get pods -l run=kubernetes-bootcamp # pod list with label
kubectl get services -l run=kubernetes-bootcamp # service list with label
kubectl label pod $POD_NAME app=v1 # pod 에 version label 붙이기
kubectl describe pods $POD_NAME # new label 이 사용된 pods의 리스트를 보자

kubectl delete service -l run=kubernetes-bootcamp # 서비스 삭제하기
```
## Scaling app
- 지금까지는 app 구동을 위해 단 하나의 파드만을 생성했으나, 트래픽이 증가하면, 사용자 요청에 맞추어 애플리케이션 규모를 조정할 필요가 있다.
- 디플로이먼트 복제 수를 변경하면 스케일링이 수행된다.
- 쿠버네티스는 오토스케일링도 지원한다. (0으로 스케일링도 지원)

```bash
kubectl get deployments # deploy 확인
kubectl get rs # replica set 확인
kubectl scale deployments/kubernetes-bootcamp --replicas=4 # deploy로 4개의 replica 생성
kubectl get deployments # 4개의 replica 로 된 것을 확인
kubectl get pods -o wide # 4개의 random string과 함께 각자의 replica 가 생성된 것을 확인
kubectl describe deployments/kubernetes-bootcamp # 상황을 보도록 하자.

kubectl describe services/kubernetes-bootcamp
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080 # 없는 경우 서비스 다시 생성

# 서로 다른 replica pod에서 response 가 오는 것을 볼 수 있음.
curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-57978f5f5d-wg9nh | v=1
curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-57978f5f5d-gxl55 | v=1
curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-57978f5f5d-4sxjw | v=1

# Scale down
kubectl scale deployments/kubernetes-bootcamp --replicas=2
kubectl get deployments # 2개의 replica 로 된 것을 확인
kubectl get pods -o wide # 2개가 Terminated 되는 것을 확인할 수 있음.
```
