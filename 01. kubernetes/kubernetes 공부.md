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

```