# 项目介绍

项目初始结构通过kubebuilder(https://github.com/kubernetes-sigs/kubebuilder)生成

kubebuilder使用文档：https://book.kubebuilder.io/cronjob-tutorial/cronjob-tutorial.html

```
kubebuilder init --domain volcengine.com --repo https://github.com/bytedance/monolith/blob/master/deploy --skip-go-version-check

kubebuilder create api --group mlplatform --version v1 --kind MLService --controller --resource
```

# 安装部署

配置好集群kubeconfig后执行以下命令：

```
make deploy # 安装CRD，部署controller
```

# MLServiceController

- CRD: `MLService`
    ```go
    // RoleSpec defines the desired state of a role in MLService
    type RoleSpec struct {
        // Name of the role
        Name string `json:"name"`

        // Number of shards for the role, each shard associated with a Deployment
        ShardNum int32 `json:"shardNum,omitempty"`

        // Template of the DeploymentSpec
        Template DeploymentTemplateSpec `json:"template"`

        ServiceSpec *ServiceSpec `json:"serviceSpec,omitempty"`
    }

    // MLServiceSpec defines the desired state of MLService
    type MLServiceSpec struct {
        // selector is a label query over deployment.
        // It must match the deployment template's labels.
        Selector *metav1.LabelSelector `json:"selector"`

        // Roles defines desired state for each role in the service
        Roles []RoleSpec `json:"roles"`
    }
    ```
- Reconciler: `MLServiceReconciler`
    - `DeploymentHandler`: Create a Deployment based on `MLService.Spec.Roles[].Template`.
    - `ServiceHandler`: Create a Service based on `MLService.Spec.Roles[].ServiceSpec`.
